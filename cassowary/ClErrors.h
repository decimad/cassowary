// $Id: ClErrors.h,v 1.24 2005/10/20 04:25:21 gjb Exp $
//
// Cassowary Incremental Constraint Solver
// Original Smalltalk Implementation by Alan Borning
// This C++ Implementation by Greg J. Badros, <gjb@cs.washington.edu>
// http://www.cs.washington.edu/homes/gjb
// (C) 1998, 1999 Greg J. Badros and Alan Borning
// See ../LICENSE for legal details regarding this software
//
// ClErrors.h

#ifndef ClErrors_H
#define ClErrors_H

#if defined(HAVE_CONFIG_H) && !defined(CONFIG_H_INCLUDED) &&                   \
    !defined(CONFIG_INLINE_H_INCLUDED)
#include "config-inline.h"
#define CONFIG_INLINE_H_INCLUDED
#endif

#include "Cassowary.h"
#include "ClSet.h"
#include "ClTypedefs.h"
#include <string.h>
#include <stdexcept>

#ifdef USE_GC
class ExCLError : public std::exception, public gc {
#else
class ExCLError : public std::exception {
#endif

  public:
    ExCLError() : _msg(NULL) {}
    virtual std::string description() const {
        return "(ExCLError) An error has occured in CL";
    }

    virtual ~ExCLError() throw() {}

  protected:
    char *_msg;
};

class ExCLInternalError : public ExCLError {
  public:
    ExCLInternalError(const char *sz) { _msg = strdup(sz); }
    virtual ~ExCLInternalError() throw() {}

    virtual std::string description() const {
        if (_msg)
            return _msg;
        else
            return "(ExCLInternalError) An internal error has occurred";
    }
};

class ExCLBadResolve : public ExCLError {
  public:
    ExCLBadResolve(const char *sz) { _msg = strdup(sz); }
    virtual ~ExCLBadResolve() throw() {}

    virtual std::string description() const {
        if (_msg)
            return _msg;
        else
            return "(ExCLBadResolve) Number of resolve values did not match "
                   "number of edit vars";
    }
};

class ExCLEditMisuse : public ExCLError {
  public:
    ExCLEditMisuse(const char *sz) { _msg = strdup(sz); }

    virtual ~ExCLEditMisuse() throw() {}

    virtual std::string description() const {
        if (_msg)
            return _msg;
        return "(ExCLEditMisuse) Edit protocol usage violation";
    }
};

class ExCLTooDifficult : public ExCLError {
  public:
    virtual ~ExCLTooDifficult() throw() {}

    virtual std::string description() const {
        return "(ExCLTooDifficult) The constraints are too difficult to solve";
    }
};

class ExCLTooDifficultSpecial : public ExCLTooDifficult {
  public:
    ExCLTooDifficultSpecial(const char *sz) { _msg = strdup(sz); }

    virtual ~ExCLTooDifficultSpecial() throw() {}

    virtual std::string description() const {
        if (_msg)
            return _msg;
        else
            return "(ExCLTooDifficultSpecial) Solver requirements are not "
                   "satisfied";
    }
};

class ExCLReadOnlyNotAllowed : public ExCLTooDifficult {
  public:
    virtual ~ExCLReadOnlyNotAllowed() throw() {}

    virtual std::string description() const {
        return "(ExCLReadOnlyNotAllowed) The read-only annotation is not "
               "permitted by the solver";
    }
};

class ExCLCycleNotAllowed : public ExCLTooDifficult {
  public:
    virtual ~ExCLCycleNotAllowed() throw() {}
    virtual std::string description() const {
        return "(ExCLCycleNotAllowed) A cyclic constraint graph is not "
               "permitted by the solver";
    }
};

class ExCLStrictInequalityNotAllowed : public ExCLTooDifficult {
  public:
    virtual ~ExCLStrictInequalityNotAllowed() throw() {}

    virtual std::string description() const {
        return "(ExCLStrictInequalityNotAllowed) The strict inequality is not "
               "permitted by the solver";
    }
};

class ExCLRequiredFailure : public ExCLError {
  public:
    virtual ~ExCLRequiredFailure() throw() {}
    virtual std::string description() const {
        return "(ExCLRequiredFailure) A required constraint cannot be "
               "satisfied";
    }
};

class ExCLNotEnoughStays : public ExCLError {
  public:
    virtual ~ExCLNotEnoughStays() throw() {}
    virtual std::string description() const {
        return "(ExCLNotEnoughStays) There are not enough stays to give "
               "specific values to every variable";
    }
};

class ExCLNonlinearExpression : public ExCLError {
  public:
    virtual ~ExCLNonlinearExpression() throw() {}
    virtual std::string description() const {
        return "(ExCLNonlinearExpression) The resulting expression would be "
               "nonlinear";
    }
};

class ExCLConstraintNotFound : public ExCLError {
  public:
    virtual ~ExCLConstraintNotFound() throw() {}
    virtual std::string description() const {
        return "(ExCLConstraintNotFound) Tried to remove a constraint that was "
               "never added";
    }
};

class ExCLParseError : public ExCLError {
  public:
    virtual ~ExCLParseError() throw() {}
    virtual std::string description() const { return "(ExCLParseError)"; }
};

class ExCLParseErrorMisc : public ExCLParseError {
  public:
    ExCLParseErrorMisc(const std::string &s) : _msg("(ExCLParseError) ") {
        _msg += s;
    }
    virtual ~ExCLParseErrorMisc() throw() {}
    virtual std::string description() const { return _msg; }

  private:
    std::string _msg;
};

class ExCLParseErrorBadIdentifier : public ExCLParseError {
  public:
    ExCLParseErrorBadIdentifier(const std::string &id)
        : _msg("(ExCLParseErrorBadIdentifier) Did not recognize identifier '") {
        _msg += id;
        _msg += "'";
    }
    virtual ~ExCLParseErrorBadIdentifier() throw() {}
    virtual std::string description() const { return _msg; }

  private:
    std::string _msg;
};

class ExCLRequiredFailureWithExplanation : public ExCLRequiredFailure {
  public:
    virtual ~ExCLRequiredFailureWithExplanation() throw() {}
    virtual std::string description() const {
        return "(ExCLRequiredFailureWithExplanation) A required constraint "
               "cannot be satisfied";
    }
    virtual void AddConstraint(const ClConstraint *cnExpl) {
        _explanation.insert(cnExpl);
    }
    virtual const ClConstraintSet &explanation() const { return _explanation; }

  protected:
    ClConstraintSet _explanation;
};

#endif
