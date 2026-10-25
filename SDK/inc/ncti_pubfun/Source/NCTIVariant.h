#ifndef NCTIVariant_H
#define NCTIVariant_H

#include <string>
#include <vector>
#include <map>
#include <type_traits>
#include <memory>
#include "dcl_ncti_pubfun.h"
#include "NctiPosition.h"
#include "NctiVector.h"

namespace NCTI
{
	class NctiDisplayObject;
	class DECL_NCTI_PUBFUN MapVariant {
	private:
		enum class Type {
			Long, Double, String, VectorString, VectorLong
		};

		Type current_type;
		union {
			long long_val;
			double double_val;
			std::string string_val;
			std::vector<std::string> vector_string_val;
			std::vector<long> vector_long_val;
		};

	public:
		MapVariant();
		MapVariant(long val);
		MapVariant(double val);
		MapVariant(const std::string& val);
		MapVariant(const std::vector<std::string>& val);
		MapVariant(const std::vector<long>& val);
		MapVariant(const MapVariant& other);
		MapVariant(const NctiPosition& val);
		~MapVariant();

		MapVariant& operator=(const MapVariant& other);

		template<typename T>
		T& get() {
			void* ptr = nullptr;
			switch (current_type) {
			case Type::Long: ptr = &long_val; break;
			case Type::Double: ptr = &double_val; break;
			case Type::String: ptr = &string_val; break;
			case Type::VectorString: ptr = &vector_string_val; break;
			case Type::VectorLong: ptr = &vector_long_val; break;
			default: throw std::runtime_error("Bad variant access");
			}

			if ((std::is_same<T, long>::value && current_type == Type::Long) ||
				(std::is_same<T, double>::value && current_type == Type::Double) ||
				(std::is_same<T, std::string>::value && current_type == Type::String) ||
				(std::is_same<T, std::vector<std::string>>::value && current_type == Type::VectorString) ||
				(std::is_same<T, std::vector<long>>::value && current_type == Type::VectorLong)) {
				return *static_cast<T*>(ptr);
			}

			throw std::runtime_error("Bad variant access: type mismatch");
		}

		template<typename T>
		const T& get() const {
			const void* ptr = nullptr;
			switch (current_type) {
			case Type::Long: ptr = &long_val; break;
			case Type::Double: ptr = &double_val; break;
			case Type::String: ptr = &string_val; break;
			case Type::VectorString: ptr = &vector_string_val; break;
			case Type::VectorLong: ptr = &vector_long_val; break;
			default: throw std::runtime_error("Bad variant access");
			}

			if ((std::is_same<T, long>::value && current_type == Type::Long) ||
				(std::is_same<T, double>::value && current_type == Type::Double) ||
				(std::is_same<T, std::string>::value && current_type == Type::String) ||
				(std::is_same<T, std::vector<std::string>>::value && current_type == Type::VectorString) ||
				(std::is_same<T, std::vector<long>>::value && current_type == Type::VectorLong)) {
				return *static_cast<const T*>(ptr);
			}

			throw std::runtime_error("Bad variant access: type mismatch");
		}

		template<typename T>
		bool holds_alternative() const {
			return (std::is_same<T, long>::value && current_type == Type::Long) ||
				(std::is_same<T, double>::value && current_type == Type::Double) ||
				(std::is_same<T, std::string>::value && current_type == Type::String) ||
				(std::is_same<T, std::vector<std::string>>::value && current_type == Type::VectorString) ||
				(std::is_same<T, std::vector<long>>::value && current_type == Type::VectorLong);
		}

		size_t index() const { return static_cast<size_t>(current_type); }
	};

	class DECL_NCTI_PUBFUN NCTI_Variant {
	private:
		enum class Type {
			Long, Double, String, Ncti_Position, Ncti_Vector, VectorString, NCTI_Map
		};

		Type current_type;
		union {
			long long_val;
			double double_val;
			std::string string_val;
			NctiPosition position_val;
			NctiVector vector_val;
			std::vector<std::string> vector_string_val;
			std::map<std::string, MapVariant> map_val;
		};

	public:
		NCTI_Variant(long val);
		NCTI_Variant(double val);
		NCTI_Variant(const std::string& val);
		NCTI_Variant(const NctiPosition& val);
		NCTI_Variant(const NctiVector& val);
		NCTI_Variant(const std::vector<std::string>& val);
		NCTI_Variant(const std::map<std::string, MapVariant>& val);
		NCTI_Variant(const NCTI_Variant& other);
		~NCTI_Variant();

		NCTI_Variant& operator=(const NCTI_Variant& other);

		template<typename T>
		T& get() {
			void* ptr = nullptr;
			switch (current_type) {
			case Type::Long: ptr = &long_val; break;
			case Type::Double: ptr = &double_val; break;
			case Type::String: ptr = &string_val; break;
			case Type::Ncti_Position: ptr = &position_val; break;
			case Type::Ncti_Vector: ptr = &vector_val; break;
			case Type::VectorString: ptr = &vector_string_val; break;
			case Type::NCTI_Map: ptr = &map_val; break;
			default: throw std::runtime_error("Bad variant access");
			}

			if ((std::is_same<T, long>::value && current_type == Type::Long) ||
				(std::is_same<T, double>::value && current_type == Type::Double) ||
				(std::is_same<T, std::string>::value && current_type == Type::String) ||
				(std::is_same<T, NctiPosition>::value && current_type == Type::Ncti_Position) ||
				(std::is_same<T, NctiVector>::value && current_type == Type::Ncti_Vector) ||
				(std::is_same<T, std::vector<std::string>>::value && current_type == Type::VectorString) ||
				(std::is_same<T, std::map<std::string, MapVariant>>::value && current_type == Type::NCTI_Map)) {
				return *static_cast<T*>(ptr);
			}

			throw std::runtime_error("Bad variant access: type mismatch");
		}

		template<typename T>
		const T& get() const {
			const void* ptr = nullptr;
			switch (current_type) {
			case Type::Long: ptr = &long_val; break;
			case Type::Double: ptr = &double_val; break;
			case Type::String: ptr = &string_val; break;
			case Type::Ncti_Position: ptr = &position_val; break;
			case Type::Ncti_Vector: ptr = &vector_val; break;
			case Type::VectorString: ptr = &vector_string_val; break;
			case Type::NCTI_Map: ptr = &map_val; break;
			default: throw std::runtime_error("Bad variant access");
			}

			if ((std::is_same<T, long>::value && current_type == Type::Long) ||
				(std::is_same<T, double>::value && current_type == Type::Double) ||
				(std::is_same<T, std::string>::value && current_type == Type::String) ||
				(std::is_same<T, NctiPosition>::value && current_type == Type::Ncti_Position) ||
				(std::is_same<T, NctiVector>::value && current_type == Type::Ncti_Vector) ||
				(std::is_same<T, std::vector<std::string>>::value && current_type == Type::VectorString) ||
				(std::is_same<T, std::map<std::string, MapVariant>>::value && current_type == Type::NCTI_Map)) {
				return *static_cast<const T*>(ptr);
			}

			throw std::runtime_error("Bad variant access: type mismatch");
		}

		template<typename T>
		bool holds_alternative() const {
			return (std::is_same<T, long>::value && current_type == Type::Long) ||
				(std::is_same<T, double>::value && current_type == Type::Double) ||
				(std::is_same<T, std::string>::value && current_type == Type::String) ||
				(std::is_same<T, NctiPosition>::value && current_type == Type::Ncti_Position) ||
				(std::is_same<T, NctiVector>::value && current_type == Type::Ncti_Vector) ||
				(std::is_same<T, std::vector<std::string>>::value && current_type == Type::VectorString) ||
				(std::is_same<T, std::map<std::string, MapVariant>>::value && current_type == Type::NCTI_Map);
		}

		size_t index() const { return static_cast<size_t>(current_type); }
	};

	using NCTI_Map = std::map<std::string, MapVariant>;

	//Ncti variant
    class Ncti_VariantValue;

	template<typename T> struct Ncti_VariantTypeTraits {
		static bool check(const Ncti_VariantValue&) {
			return false;
		}
	};
	template<> struct Ncti_VariantTypeTraits<std::nullptr_t>;
	template<> struct Ncti_VariantTypeTraits<bool>;
	template<> struct Ncti_VariantTypeTraits<int>;
	template<> struct Ncti_VariantTypeTraits<long>;
	template<> struct Ncti_VariantTypeTraits<long long>;
	template<> struct Ncti_VariantTypeTraits<double>;
	template<> struct Ncti_VariantTypeTraits<std::string>;
	template<> struct Ncti_VariantTypeTraits<std::vector<uint8_t>>;
	template<> struct Ncti_VariantTypeTraits<std::vector<Ncti_VariantValue>>;
	template<> struct Ncti_VariantTypeTraits<std::map<std::string, Ncti_VariantValue>>;
	template<> struct Ncti_VariantTypeTraits<NctiPosition>;
	template<> struct Ncti_VariantTypeTraits<NctiVector>;
	template<> struct Ncti_VariantTypeTraits<NctiDisplayObject*>;
	template<> struct Ncti_VariantTypeTraits<void*>;

    class DECL_NCTI_PUBFUN Ncti_BaseVariant {
    public:
        virtual ~Ncti_BaseVariant() = default;

        virtual bool isNull() const { return false; }
        virtual bool isBool() const { return false; }
        virtual bool isInt() const { return false; }
        virtual bool isLong() const { return false; }
        virtual bool isInt64() const { return false; }
        virtual bool isDouble() const { return false; }
        virtual bool isString() const { return false; }
        virtual bool isBytes() const { return false; }
        virtual bool isList() const { return false; }
        virtual bool isMap() const { return false; }
        //virtual bool isSet() const { return false; }
        virtual bool isPosition() const { return false; }
		virtual bool isVector() const { return false; }
		virtual bool isDisplayObjectPtr() const { return false; }
		virtual bool isVoidPtr() const { return false; }

        enum class Type {
            Null,
            Bool,
            Int,
            Long,
            Int64,
            Double,
            String,
            Bytes,
            List,
            Map,
            Set,
            Ncti_Position,
            Ncti_Vector,
			NctiDisplayObjectPtr,
			VoidPtr
        };

        virtual Type getType() const = 0;
        virtual std::unique_ptr<Ncti_BaseVariant> clone() const = 0;

		virtual bool& getBool();
		virtual int& getInt();
		virtual long& getLong();
		virtual long long& getInt64();
		virtual double& getDouble();
		virtual std::string& getString();
		virtual std::vector<uint8_t>& getBytes();
		virtual std::vector<Ncti_VariantValue>& getList();
		virtual std::map<std::string, Ncti_VariantValue>& getMap();
		virtual NctiPosition& getPosition();
		virtual NctiVector& getVector();
		virtual NctiDisplayObject* getDisplayObjectPtr();
		virtual void* getVoidPtr();

		virtual const bool& getBool() const;
		virtual const int& getInt() const;
		virtual const long& getLong() const;
		virtual const long long& getInt64() const;
		virtual const double& getDouble() const;
		virtual const std::string& getString() const;
		virtual const std::vector<uint8_t>& getBytes() const;
		virtual const std::vector<Ncti_VariantValue>& getList() const;
		virtual const std::map<std::string, Ncti_VariantValue>& getMap() const;
		virtual const NctiPosition& getPosition() const;
		virtual const NctiVector& getVector() const;
		virtual const NctiDisplayObject* getDisplayObjectPtr() const;
		virtual const void* getVoidPtr() const;

        virtual void print(int indent = 0) const = 0;
    };

    class DECL_NCTI_PUBFUN Ncti_VariantValue {
    public:
        using Type = Ncti_BaseVariant::Type;

    private:
        std::unique_ptr<Ncti_BaseVariant> m_ptr;

    public:
        Ncti_VariantValue();
        Ncti_VariantValue(Ncti_VariantValue&& other) noexcept;
        Ncti_VariantValue& operator=(Ncti_VariantValue&& other) noexcept;
        Ncti_VariantValue(const Ncti_VariantValue& other);
        Ncti_VariantValue& operator=(const Ncti_VariantValue& other);

        ~Ncti_VariantValue() = default;

        explicit Ncti_VariantValue(std::nullptr_t);
        explicit Ncti_VariantValue(bool val);
        explicit Ncti_VariantValue(int val);
        explicit Ncti_VariantValue(long val);
        explicit Ncti_VariantValue(long long val);
        explicit Ncti_VariantValue(double val);
        explicit Ncti_VariantValue(const std::string& val);
        explicit Ncti_VariantValue(std::string&& val);
        explicit Ncti_VariantValue(const std::vector<uint8_t>& val);
        explicit Ncti_VariantValue(std::vector<uint8_t>&& val);
        explicit Ncti_VariantValue(const std::vector<Ncti_VariantValue>& val);
        explicit Ncti_VariantValue(std::vector<Ncti_VariantValue>&& val);
        explicit Ncti_VariantValue(const std::map<std::string, Ncti_VariantValue>& val);
        explicit Ncti_VariantValue(std::map<std::string, Ncti_VariantValue>&& val);
        //explicit Ncti_VariantValue(std::set<Ncti_VariantValue> val);
        explicit Ncti_VariantValue(const NctiPosition& val);
        explicit Ncti_VariantValue(NctiPosition&& val);
        explicit Ncti_VariantValue(const NctiVector& val);
		explicit Ncti_VariantValue(NctiVector&& val);
		explicit Ncti_VariantValue(NctiDisplayObject* val);
		explicit Ncti_VariantValue(void* val);

        bool isNull() const;
        bool isBool() const;
        bool isInt() const;
        bool isLong() const;
        bool isInt64() const;
        bool isDouble() const;
        bool isString() const;
        bool isBytes() const;
        bool isList() const;
        bool isMap() const;
        //bool isSet() const;
        bool isPosition() const;
		bool isVector() const;
		bool isDisplayObjectPtr() const;
		bool isVoidPtr() const;

        Type getType() const;

		template<typename T>
        bool holds_alternative() const;

        bool& getBool();
        int& getInt();
        long& getLong();
		long long& getInt64();
        double& getDouble();
        std::string& getString();
        std::vector<uint8_t>& getBytes();
        std::vector<Ncti_VariantValue>& getList();
        std::map<std::string, Ncti_VariantValue>& getMap();
        //std::set<Ncti_VariantValue>& getSet();
        NctiPosition& getPosition();
		NctiVector& getVector();
		NctiDisplayObject* getDisplayObjectPtr();
		void* getVoidPtr();

        const bool& getBool() const;
        const int& getInt() const;
        const long& getLong() const;
        const long long& getInt64() const;
        const double& getDouble() const;
        const std::string& getString() const;
        const std::vector<uint8_t>& getBytes() const;
        const std::vector<Ncti_VariantValue>& getList() const;
        const std::map<std::string, Ncti_VariantValue>& getMap() const;
        //const std::set<Ncti_VariantValue>& getSet() const;
        const NctiPosition& getPosition() const;
		const NctiVector& getVector() const;
		const NctiDisplayObject* getDisplayObjectPtr() const;
		const void* getVoidPtr() const;

        void print(int indent = 0) const;
        bool operator==(const Ncti_VariantValue& other) const;
        bool operator<(const Ncti_VariantValue& other) const;

        void swap(Ncti_VariantValue& other) noexcept;

    private:
        int getTypeOrder() const;
        std::unique_ptr<Ncti_BaseVariant> cloneBase() const;
    };
}


#endif // NCTIVariant_H