#pragma once

#include <GLECore/event/event.hpp>
#include <GLECore/event/signal.hpp>
#include <GLECore/pch.hpp>

#include <functional>

namespace gle {

    // Property changed event
    template <typename Type>
    struct PropertyChangedEvent : public Event {
      public:
        Type oldValue{};
        Type newValue{};

        // Misc
        std::string ToString() const override { return "PropertyChangedEvent"; }
    };

    // Property base
    class PropertyBase {
      public:
        virtual ~PropertyBase() = default;

        // Methods
        virtual const std::string GetName() const { return "Property"; }
        virtual std::string GetTypeName() const { return "NULL"; }
        virtual std::string ToString() const { return "Property"; }
    };

    // Property
    template <typename Type>
    class Property : public PropertyBase {
      public:
        using WriteCallback = std::function<bool(Type &newValue, Type &oldValue)>;

        // Constructors
      public:
        Property() = default;

        explicit Property(const std::string &name, const Type &value = {}) : name(name), value(value) {}

        Property(const std::string &name, const Type &value, WriteCallback callback)
            : name(name), value(value), callback(std::move(callback)) {}

        template <typename InstanceType>
        Property(const std::string &name, const Type &value, InstanceType *instance,
                 bool (InstanceType::*method)(Type &, Type &))
            : name(name), value(value) {

            callback = [instance, method](Type &newValue, Type &oldValue) -> bool {
                return (instance->*method)(newValue, oldValue);
            };
        }

      public:
        // Methods
        void Set(const Type &newValue) {
            Type oldValue = value;
            Type modifiedValue = newValue;

            if (callback) {
                if (!callback(modifiedValue, oldValue))
                    return;
            }

            if (value == modifiedValue)
                return;

            value = modifiedValue;

            PropertyChangedEvent<Type> event;
            event.oldValue = oldValue;
            event.newValue = value;

            Changed.Fire(event);
        }

        const Type &Get() const { return value; }

        // Property base implementation
        const std::string GetName() const override { return name; }

        std::string GetTypeName() const override { return typeid(Type).name(); }

        std::string ToString() const override {
            if constexpr (requires { value.ToString(); }) {
                return value.ToString();
            } else if constexpr (std::is_same_v<Type, std::string>) {
                return value;
            } else {
                return std::to_string(value);
            }
        }

      public:
        // Conversion
        operator const Type &() const { return value; }

        // Operators
        Property<Type> &operator=(const Type &newValue) {
            Set(newValue);
            return *this;
        }

        Property<Type> &operator+=(const Type &other) {
            Set(value + other);
            return *this;
        }

        Property<Type> &operator-=(const Type &other) {
            Set(value - other);
            return *this;
        }

        Property<Type> &operator*=(const Type &other) {
            Set(value * other);
            return *this;
        }

        Property<Type> &operator/=(const Type &other) {
            Set(value / other);
            return *this;
        }

      public:
        Signal<PropertyChangedEvent<Type>> Changed;

      private:
        std::string name;
        Type value{};
        WriteCallback callback;
    };

    // Types
    using PropertyList = std::vector<std::shared_ptr<PropertyBase>>;

} // namespace gle