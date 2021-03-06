// $Id: ClMap.h,v 1.5 1999/04/20 00:25:03 gjb Exp $
// Cassowary Incremental Constraint Solver
// Original Smalltalk Implementation by Alan Borning
// This C++ Implementation by Greg J. Badros, <gjb@cs.washington.edu>
// http://www.cs.washington.edu/homes/gjb
// (C) 1998, 1999 Greg J. Badros and Alan Borning
// See ../LICENSE for legal details regarding this software
//
// ClMap.h
// Define a map templated type, either as a hash_map or as a regular map
// depending on makefile cpp flag CL_USE_HASH_MAP_AND_SET

#ifndef CL_MAP_H
#define CL_MAP_H

#if defined(HAVE_CONFIG_H) && !defined(CONFIG_H_INCLUDED) &&                   \
    !defined(CONFIG_INLINE_H_INCLUDED)
#include "config-inline.h"
#define CONFIG_INLINE_H_INCLUDED
#endif

#ifdef CL_USE_HASH_MAP_AND_SET
#include <unordered_map>

template< typename Key, typename Value, typename Predicate = std::less<Key>, typename Allocator = std::allocator<std::pair<Key,Value>> >
using ClMap = std::unordered_map<Key, Value, Predicate, Allocator>;

#else
#include <map>

template< typename Key, typename Value, typename Predicate = std::less<Key>, typename Allocator = std::allocator<std::pair<const Key,Value>> >
using ClMap = std::map<Key, Value, Predicate, Allocator>;

#endif

#endif
