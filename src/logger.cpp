// Copyright (c) 2021 Sergey Bazhnev <SBazhnev@gmail.com>
// Licensed under the MIT License
//

#include "logger.h"

#include <iostream>
#include <string>

#include <boost/core/null_deleter.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/support/date_time.hpp>

namespace attrs     = boost::log::attributes;
namespace expr      = boost::log::expressions;
namespace keywords  = boost::log::keywords;
namespace logging   = boost::log;
namespace sinks     = boost::log::sinks;
namespace src       = boost::log::sources;
namespace trivial   = boost::log::trivial;

BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp,"TimeStamp",boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(severity,"Severity",trivial::severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(named_scope,"Scope",attrs::named_scope::value_type)

const trivial::severity_level k_severity_level =
#ifdef NDEBUG
    trivial::info;
#else
    trivial::trace;
#endif // NDEBUG

const logging::formatter k_formatter
    (
        expr::format("%1% [%2%] [%3%]: %4%") %
        expr::format_date_time(timestamp,"%H:%M:%S.%f") %
        severity %
        expr::format_named_scope(named_scope,keywords::format = "%n",keywords::iteration = expr::forward) %
        expr::smessage
    );

const std::string       k_logs_storage             = "logs";
const std::string       k_log_file_name_template   = "%Y%m%d_%N.log";

constexpr std::size_t   k_log_file_rotation_size   = 10 * 1024 * 1024;
const auto              k_log_file_time_rotation   = sinks::file::rotation_at_time_point(0,0,0);
constexpr bool          k_log_file_auto_flush      = true;

constexpr std::size_t   k_logs_max_size            = 100*1024*1024;
constexpr std::size_t   k_logs_min_free_space      = 100*1024*1024;

void logger_configuration();

BOOST_LOG_GLOBAL_LOGGER_INIT(logger,src::severity_logger_mt)
{
  src::severity_logger_mt<trivial::severity_level> logger;

  logger.add_attribute(timestamp.get_name(),attrs::local_clock());
  logger.add_attribute(named_scope.get_name(),attrs::named_scope());

  logger_configuration();

  return logger;
}

void logger_configuration()
{
  boost::shared_ptr<logging::core> log_core(logging::core::get());

  // console logging
  auto console_backend = boost::make_shared<sinks::text_ostream_backend>();
  console_backend->auto_flush();
  console_backend->add_stream(boost::shared_ptr<std::ostream>(&std::clog,boost::null_deleter()));

  using TextSink = sinks::synchronous_sink<sinks::text_ostream_backend>;
  auto console_sink = boost::make_shared<TextSink>(console_backend);

  console_sink->set_formatter(k_formatter);

  log_core->add_sink(console_sink);

  // file logging
  auto file_backend = boost::make_shared<sinks::text_file_backend>
      (
          keywords::file_name = k_log_file_name_template,
          keywords::rotation_size = k_log_file_rotation_size,
          keywords::time_based_rotation = k_log_file_time_rotation,
          keywords::auto_flush = k_log_file_auto_flush
      );

  using FileTextSink = sinks::synchronous_sink<sinks::text_file_backend>;
  auto file_sink = boost::make_shared<FileTextSink>(file_backend);

  file_sink->set_formatter(k_formatter);

  log_core->add_sink(file_sink);

  // logs collector
  file_backend->set_file_collector(sinks::file::make_collector
      (
          keywords::target = k_logs_storage,
          keywords::max_size = k_logs_max_size,
          keywords::min_free_space = k_logs_min_free_space
      ));

  try
  {
    file_backend->scan_for_files(sinks::file::scan_all);
  }
  catch (const std::exception& ex)
  {
    LERROR << "The logs scan exception: " << ex.what();
  }

  // set log level
  log_core->set_filter(severity >= k_severity_level);
}
