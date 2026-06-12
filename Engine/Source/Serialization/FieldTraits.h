#pragma once

#include "Core/Minimal.h"

namespace Source::Serialization
{
    template <typename T> struct FieldTraits;

    template <> struct FieldTraits<uint8>
    {
        static constexpr const char* TypeName = "uint8";
        static Json ToJson(const uint8& V) { return V; }
        static uint8 FromJson(const Json& J) { return J.get<uint8>(); }
    };
    
    template <> struct FieldTraits<uint16>
    {
        static constexpr const char* TypeName = "uint16";
        static Json ToJson(const uint16& V) { return V; }
        static uint16 FromJson(const Json& J) { return J.get<uint16>(); }
    };
    
    template <> struct FieldTraits<uint32>
    {
        static constexpr const char* TypeName = "uint32";
        static Json ToJson(const uint32& V) { return V; }
        static uint32 FromJson(const Json& J) { return J.get<uint32>(); }
    };
    
    template <> struct FieldTraits<uint64>
    {
        static constexpr const char* TypeName = "uint64";
        static Json ToJson(const uint64& V) { return V; }
        static uint64 FromJson(const Json& J) { return J.get<uint64>(); }
    };
    
    template <> struct FieldTraits<int64>
    {
        static constexpr const char* TypeName = "int64";
        static Json ToJson(const int64& V) { return V; }
        static int64 FromJson(const Json& J) { return J.get<int64>(); }
    };
    
    template <> struct FieldTraits<int32>
    {
        static constexpr const char* TypeName = "int";
        static Json ToJson(const int& V) { return V; }
        static int32 FromJson(const Json& J) { return J.get<int>(); }
    };
    
    template <> struct FieldTraits<float>
    {
        static constexpr const char* TypeName = "float";
        static Json ToJson(const float& V) { return V; }
        static float FromJson(const Json& J) { return J.get<float>(); }
    };
    
    template <> struct FieldTraits<bool>
    {
        static constexpr const char* TypeName = "bool";
        static Json ToJson(const bool& V) { return V; }
        static bool FromJson(const Json& J) { return J.get<bool>(); }
    };
    
    template <> struct FieldTraits<std::string>
    {
        static constexpr const char* TypeName = "string";
        static Json ToJson(const std::string& V) { return V; }
        static std::string FromJson(const Json& J) { return J.get<std::string>(); }
    };
    
    template <> struct FieldTraits<Vector2>
    {
        static constexpr const char* TypeName = "vec2";
        static Json ToJson(const Vector2& V) { return Json::array({ V.x, V.y }); }
        static Vector2 FromJson(const Json& J) { return { J.at(0).get<float>(), J.at(1).get<float>() }; }
    };
    
    template <> struct FieldTraits<Vector3>
    {
        static constexpr const char* TypeName = "vec3";
        static Json ToJson(const Vector3& V) { return Json::array({ V.x, V.y, V.z }); }
        static Vector3 FromJson(const Json& J) { return { J.at(0).get<float>(), J.at(1).get<float>(), J.at(2).get<float>() }; }
    };
    
    template <> struct FieldTraits<Vector4>
    {
        static constexpr const char* TypeName = "vec4";
        static Json ToJson(const Vector4& V) { return Json::array({ V.x, V.y, V.z, V.w }); }
        static Vector4 FromJson(const Json& J) { return { J.at(0).get<float>(), J.at(1).get<float>(), J.at(2).get<float>(), J.at(3).get<float>() }; }
    };
}