// Copyright (c) 2021 Sergey Bazhnev <SBazhnev@gmail.com>
// Licensed under the MIT License
//

#ifndef LOGGER_H_
#define LOGGER_H_

#define BOOST_LOG_DYN_LINK 1

#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/trivial.hpp>

BOOST_LOG_GLOBAL_LOGGER(logger,boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>);

//
#define LTRACE          BOOST_LOG_SEV(logger::get(),boost::log::trivial::trace)
#define LDEBUG          BOOST_LOG_SEV(logger::get(),boost::log::trivial::debug)
#define LINFO           BOOST_LOG_SEV(logger::get(),boost::log::trivial::info)
#define LWARNING        BOOST_LOG_SEV(logger::get(),boost::log::trivial::warning)
#define LERROR          BOOST_LOG_SEV(logger::get(),boost::log::trivial::error)
#define LFATAL          BOOST_LOG_SEV(logger::get(),boost::log::trivial::fatal)

//
#define LNAMED_SCOPE(s) BOOST_LOG_NAMED_SCOPE(s);

#endif // LOGGER_H_
