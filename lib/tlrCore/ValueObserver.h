// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2021-2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tlrCore/Observer.h>
#include <tlrCore/Util.h>

#include <functional>
#include <memory>
#include <vector>

namespace tlr
{
    namespace observer
    {
        template<typename T>
        class IValue;

        //! Value observer.
        template<typename T>
        class ValueObserver : public std::enable_shared_from_this<ValueObserver<T> >
        {
            TLR_NON_COPYABLE(ValueObserver);

        protected:
            void _init(
                const std::weak_ptr<IValue<T> >&,
                const std::function<void(const T&)>&,
                CallbackAction);

            ValueObserver();

        public:
            ~ValueObserver();

            //! Create a new value observer.
            static std::shared_ptr<ValueObserver<T> > create(
                const std::weak_ptr<IValue<T> >&,
                const std::function<void(const T&)>&,
                CallbackAction = CallbackAction::Trigger);

            //! Execute the callback.
            void doCallback(const T&);

        private:
            std::function<void(const T&)> _callback;
            std::weak_ptr<IValue<T> > _value;
        };

        //! Base class for a value.
        template<typename T>
        class IValue
        {
        public:
            virtual ~IValue() = 0;

            //! Get the value.
            virtual const T& get() const = 0;

            //! Get the number of observers.
            std::size_t getObserversCount() const;

        protected:
            void _add(const std::weak_ptr<ValueObserver<T> >&);
            void _removeExpired();

            std::vector<std::weak_ptr<ValueObserver<T> > > _observers;

            friend class ValueObserver<T>;
        };

        //! Value.
        template<typename T>
        class Value : public IValue<T>
        {
            TLR_NON_COPYABLE(Value);

        protected:
            Value();
            explicit Value(const T&);

        public:
            //! Create a new value.
            static std::shared_ptr<Value<T> > create();

            //! Create a new value.
            static std::shared_ptr<Value<T> > create(const T&);

            //! Set the value.
            void setAlways(const T&);

            //! Set the value only if it has changed.
            bool setIfChanged(const T&);

            const T& get() const override;

        private:
            T _value = T();
        };

    }
}

#include <tlrCore/ValueObserverInline.h>

