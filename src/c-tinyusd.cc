// SPDX-License-Identifier: Apache 2.0
// Copyright 2022-Present Light Transport Entertainment Inc.

#include "c-tinyusd.h"

#include "tinyusdz.hh"
#include "tydra/scene-access.hh"
#include "usdLux.hh"
#include "prim-pprint.hh"
#include "pprinter.hh"
#include "value-pprint.hh"
#include "common-macros.inc"
#include "str-util.hh"
#include "value-types.hh"

// TODO:
// - [ ] Implement our own `strlen`

CTinyUSDValueType c_tinyusd_value_type(const CTinyUSDValue *value) {
  if (!value) {
    return C_TINYUSD_VALUE_UNKNOWN;
  }

  const tinyusdz::value::Value *pv = reinterpret_cast<const tinyusdz::value::Value *>(value);
  uint32_t tyid = pv->type_id();

  bool is_array = false;
  if (tyid & tinyusdz::value::TYPE_ID_1D_ARRAY_BIT) {
    is_array = true;
    // turn of array bit
    tyid = tyid & (~tinyusdz::value::TYPE_ID_1D_ARRAY_BIT);
  }

  using namespace tinyusdz::value;

  uint32_t basety = C_TINYUSD_VALUE_UNKNOWN;

  switch (tyid) {
    case TYPE_ID_TOKEN: {
      basety = C_TINYUSD_VALUE_TOKEN;
      break;
    }
    case TYPE_ID_TOKEN_VECTOR: {
      basety = C_TINYUSD_VALUE_TOKEN_VECTOR;
      break;
    }
    case TYPE_ID_STRING:
    case TYPE_ID_STRING_DATA: {
      basety = C_TINYUSD_VALUE_STRING;
      break;
    }
    case TYPE_ID_BOOL: {
      basety = C_TINYUSD_VALUE_BOOL;
      break;
    }
    case TYPE_ID_HALF: {
      basety = C_TINYUSD_VALUE_HALF;
      break;
    }
    case TYPE_ID_HALF2: {
      basety = C_TINYUSD_VALUE_HALF2;
      break;
    }
    case TYPE_ID_HALF3: {
      basety = C_TINYUSD_VALUE_HALF3;
      break;
    }
    case TYPE_ID_HALF4: {
      basety = C_TINYUSD_VALUE_HALF4;
      break;
    }
    case TYPE_ID_INT32: {
      basety = C_TINYUSD_VALUE_INT;
      break;
    }
    case TYPE_ID_INT2: {
      basety = C_TINYUSD_VALUE_INT2;
      break;
    }
    case TYPE_ID_INT3: {
      basety = C_TINYUSD_VALUE_INT3;
      break;
    }
    case TYPE_ID_INT4: {
      basety = C_TINYUSD_VALUE_INT4;
      break;
    }
    case TYPE_ID_UINT32: {
      basety = C_TINYUSD_VALUE_UINT;
      break;
    }
    case TYPE_ID_UINT2: {
      basety = C_TINYUSD_VALUE_UINT2;
      break;
    }
    case TYPE_ID_UINT3: {
      basety = C_TINYUSD_VALUE_UINT3;
      break;
    }
    case TYPE_ID_UINT4: {
      basety = C_TINYUSD_VALUE_UINT4;
      break;
    }
    case TYPE_ID_INT64: {
      basety = C_TINYUSD_VALUE_INT64;
      break;
    }
    case TYPE_ID_UINT64: {
      basety = C_TINYUSD_VALUE_UINT64;
      break;
    }
    case TYPE_ID_FLOAT: {
      basety = C_TINYUSD_VALUE_FLOAT;
      break;
    }
    case TYPE_ID_FLOAT2: {
      basety = C_TINYUSD_VALUE_FLOAT2;
      break;
    }
    case TYPE_ID_FLOAT3: {
      basety = C_TINYUSD_VALUE_FLOAT3;
      break;
    }
    case TYPE_ID_FLOAT4: {
      basety = C_TINYUSD_VALUE_FLOAT4;
      break;
    }
    case TYPE_ID_DOUBLE: {
      basety = C_TINYUSD_VALUE_DOUBLE;
      break;
    }
    case TYPE_ID_DOUBLE2: {
      basety = C_TINYUSD_VALUE_DOUBLE2;
      break;
    }
    case TYPE_ID_DOUBLE3: {
      basety = C_TINYUSD_VALUE_DOUBLE3;
      break;
    }
    case TYPE_ID_DOUBLE4: {
      basety = C_TINYUSD_VALUE_DOUBLE4;
      break;
    }
    case TYPE_ID_QUATH: {
      basety = C_TINYUSD_VALUE_QUATH;
      break;
    }
    case TYPE_ID_QUATF: {
      basety = C_TINYUSD_VALUE_QUATF;
      break;
    }
    case TYPE_ID_QUATD: {
      basety = C_TINYUSD_VALUE_QUATD;
      break;
    }
    case TYPE_ID_COLOR3H: {
      basety = C_TINYUSD_VALUE_COLOR3H;
      break;
    }
    case TYPE_ID_COLOR3F: {
      basety = C_TINYUSD_VALUE_COLOR3F;
      break;
    }
    case TYPE_ID_COLOR3D: {
      basety = C_TINYUSD_VALUE_COLOR3D;
      break;
    }
    case TYPE_ID_COLOR4H: {
      basety = C_TINYUSD_VALUE_COLOR4H;
      break;
    }
    case TYPE_ID_COLOR4F: {
      basety = C_TINYUSD_VALUE_COLOR4F;
      break;
    }
    case TYPE_ID_COLOR4D: {
      basety = C_TINYUSD_VALUE_COLOR4D;
      break;
    }
    case TYPE_ID_TEXCOORD2H: {
      basety = C_TINYUSD_VALUE_TEXCOORD2H;
      break;
    }
    case TYPE_ID_TEXCOORD2F: {
      basety = C_TINYUSD_VALUE_TEXCOORD2F;
      break;
    }
    case TYPE_ID_TEXCOORD2D: {
      basety = C_TINYUSD_VALUE_TEXCOORD2D;
      break;
    }
    case TYPE_ID_TEXCOORD3H: {
      basety = C_TINYUSD_VALUE_TEXCOORD3H;
      break;
    }
    case TYPE_ID_TEXCOORD3F: {
      basety = C_TINYUSD_VALUE_TEXCOORD3F;
      break;
    }
    case TYPE_ID_TEXCOORD3D: {
      basety = C_TINYUSD_VALUE_TEXCOORD3D;
      break;
    }
    case TYPE_ID_NORMAL3H: {
      basety = C_TINYUSD_VALUE_NORMAL3H;
      break;
    }
    case TYPE_ID_NORMAL3F: {
      basety = C_TINYUSD_VALUE_NORMAL3F;
      break;
    }
    case TYPE_ID_NORMAL3D: {
      basety = C_TINYUSD_VALUE_NORMAL3D;
      break;
    }
    case TYPE_ID_VECTOR3H: {
      basety = C_TINYUSD_VALUE_VECTOR3H;
      break;
    }
    case TYPE_ID_VECTOR3F: {
      basety = C_TINYUSD_VALUE_VECTOR3F;
      break;
    }
    case TYPE_ID_VECTOR3D: {
      basety = C_TINYUSD_VALUE_VECTOR3D;
      break;
    }
    case TYPE_ID_POINT3H: {
      basety = C_TINYUSD_VALUE_POINT3H;
      break;
    }
    case TYPE_ID_POINT3F: {
      basety = C_TINYUSD_VALUE_POINT3F;
      break;
    }
    case TYPE_ID_POINT3D: {
      basety = C_TINYUSD_VALUE_POINT3D;
      break;
    }
    case TYPE_ID_MATRIX2F:
    case TYPE_ID_MATRIX2D: {
      basety = C_TINYUSD_VALUE_MATRIX2D;
      break;
    }
    case TYPE_ID_MATRIX3F:
    case TYPE_ID_MATRIX3D: {
      basety = C_TINYUSD_VALUE_MATRIX3D;
      break;
    }
    case TYPE_ID_MATRIX4F:
    case TYPE_ID_MATRIX4D: {
      basety = C_TINYUSD_VALUE_MATRIX4D;
      break;
    }
    case TYPE_ID_FRAME4D: {
      basety = C_TINYUSD_VALUE_FRAME4D;
      break;
    }
    case TYPE_ID_CUSTOMDATA: {
      basety = C_TINYUSD_VALUE_DICTIONARY;
      break;
    }
    // TODO
    default: {
      break;
    }
  }

  if (is_array) {
    return static_cast<CTinyUSDValueType>(basety | C_TINYUSD_VALUE_1D_BIT);
  } else {
    return static_cast<CTinyUSDValueType>(basety);
  }
}

const char *c_tinyusd_value_type_name(CTinyUSDValueType value_type) {
  // 32 should be enough length to support all C_TINYUSD_VALUE_* type name +
  // '[]'
  static thread_local char buf[32];

  bool is_array = value_type & C_TINYUSD_VALUE_1D_BIT;

  // drop array bit.
  uint32_t basety = value_type & (~C_TINYUSD_VALUE_1D_BIT);

  const char *tyname = "[invalid]";

  switch (static_cast<CTinyUSDValueType>(basety)) {
    case C_TINYUSD_VALUE_UNKNOWN: {
      break;
    }
    case C_TINYUSD_VALUE_BOOL: {
      tyname = "bool";
      break;
    }
    case C_TINYUSD_VALUE_TOKEN: {
      tyname = "token";
      break;
    }
    case C_TINYUSD_VALUE_TOKEN_VECTOR: {
      tyname = "token[]";
      is_array = false;
      break;
    }
    case C_TINYUSD_VALUE_STRING: {
      tyname = "string";
      break;
    }
    case C_TINYUSD_VALUE_STRING_VECTOR: {
      tyname = "string[]";
      is_array = false;
      break;
    }
    case C_TINYUSD_VALUE_HALF: {
      tyname = "half";
      break;
    }
    case C_TINYUSD_VALUE_HALF2: {
      tyname = "half2";
      break;
    }
    case C_TINYUSD_VALUE_HALF3: {
      tyname = "half3";
      break;
    }
    case C_TINYUSD_VALUE_HALF4: {
      tyname = "half4";
      break;
    }
    case C_TINYUSD_VALUE_INT: {
      tyname = "int";
      break;
    }
    case C_TINYUSD_VALUE_INT2: {
      tyname = "int2";
      break;
    }
    case C_TINYUSD_VALUE_INT3: {
      tyname = "int3";
      break;
    }
    case C_TINYUSD_VALUE_INT4: {
      tyname = "int4";
      break;
    }
    case C_TINYUSD_VALUE_UINT: {
      tyname = "uint";
      break;
    }
    case C_TINYUSD_VALUE_UINT2: {
      tyname = "uint2";
      break;
    }
    case C_TINYUSD_VALUE_UINT3: {
      tyname = "uint3";
      break;
    }
    case C_TINYUSD_VALUE_UINT4: {
      tyname = "uint4";
      break;
    }
    case C_TINYUSD_VALUE_INT64: {
      tyname = "int64";
      break;
    }
    case C_TINYUSD_VALUE_UINT64: {
      tyname = "uint64";
      break;
    }
    case C_TINYUSD_VALUE_FLOAT: {
      tyname = "float";
      break;
    }
    case C_TINYUSD_VALUE_FLOAT2: {
      tyname = "float2";
      break;
    }
    case C_TINYUSD_VALUE_FLOAT3: {
      tyname = "float3";
      break;
    }
    case C_TINYUSD_VALUE_FLOAT4: {
      tyname = "float4";
      break;
    }
    case C_TINYUSD_VALUE_DOUBLE: {
      tyname = "double";
      break;
    }
    case C_TINYUSD_VALUE_DOUBLE2: {
      tyname = "double2";
      break;
    }
    case C_TINYUSD_VALUE_DOUBLE3: {
      tyname = "double3";
      break;
    }
    case C_TINYUSD_VALUE_DOUBLE4: {
      tyname = "double4";
      break;
    }
    case C_TINYUSD_VALUE_QUATH: {
      tyname = "quath";
      break;
    }
    case C_TINYUSD_VALUE_QUATF: {
      tyname = "quatf";
      break;
    }
    case C_TINYUSD_VALUE_QUATD: {
      tyname = "quatd";
      break;
    }
    case C_TINYUSD_VALUE_NORMAL3H: {
      tyname = "normal3h";
      break;
    }
    case C_TINYUSD_VALUE_NORMAL3F: {
      tyname = "normal3f";
      break;
    }
    case C_TINYUSD_VALUE_NORMAL3D: {
      tyname = "normal3d";
      break;
    }
    case C_TINYUSD_VALUE_VECTOR3H: {
      tyname = "vector3h";
      break;
    }
    case C_TINYUSD_VALUE_VECTOR3F: {
      tyname = "vector3f";
      break;
    }
    case C_TINYUSD_VALUE_VECTOR3D: {
      tyname = "vector3d";
      break;
    }
    case C_TINYUSD_VALUE_POINT3H: {
      tyname = "point3h";
      break;
    }
    case C_TINYUSD_VALUE_POINT3F: {
      tyname = "point3f";
      break;
    }
    case C_TINYUSD_VALUE_POINT3D: {
      tyname = "point3d";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD2H: {
      tyname = "texCoord2h";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD2F: {
      tyname = "texCoord2f";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD2D: {
      tyname = "texCoord2d";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD3H: {
      tyname = "texCoord3h";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD3F: {
      tyname = "texCoord3f";
      break;
    }
    case C_TINYUSD_VALUE_TEXCOORD3D: {
      tyname = "texCoord3d";
      break;
    }
    case C_TINYUSD_VALUE_COLOR3H: {
      tyname = "color3h";
      break;
    }
    case C_TINYUSD_VALUE_COLOR3F: {
      tyname = "color3f";
      break;
    }
    case C_TINYUSD_VALUE_COLOR3D: {
      tyname = "color3d";
      break;
    }
    case C_TINYUSD_VALUE_COLOR4H: {
      tyname = "color4h";
      break;
    }
    case C_TINYUSD_VALUE_COLOR4F: {
      tyname = "color4f";
      break;
    }
    case C_TINYUSD_VALUE_COLOR4D: {
      tyname = "color4d";
      break;
    }
    case C_TINYUSD_VALUE_MATRIX2D: {
      tyname = "matrix2d";
      break;
    }
    case C_TINYUSD_VALUE_MATRIX3D: {
      tyname = "matrix3d";
      break;
    }
    case C_TINYUSD_VALUE_MATRIX4D: {
      tyname = "matrix4d";
      break;
    }
    case C_TINYUSD_VALUE_FRAME4D: {
      tyname = "frame4d";
      break;
    }
    case C_TINYUSD_VALUE_DICTIONARY: {
      tyname = "dictionary";
      break;
    }
    case C_TINYUSD_VALUE_END: {
      tyname = "[invalid]";
      break;
    }  // invalid
       // default: { return 0; }
  }

  uint32_t sz = static_cast<uint32_t>(strlen(tyname));

  if (sz > 31) {
    // Just in case: this should not happen though.
    sz = 31;
  }

  strncpy(buf, tyname, sz);

  if (is_array) {
    if (sz > 29) {
      // Just in case: this should not happen though.
      sz = 29;
    }

    buf[sz] = '[';
    buf[sz + 1] = ']';
    buf[sz + 2] = '\0';
  } else {
    buf[sz] = '\0';
  }

  return buf;
}

uint32_t c_tinyusd_value_type_components(CTinyUSDValueType value_type) {
  // drop array bit.
  uint32_t basety = value_type & (~C_TINYUSD_VALUE_1D_BIT);

  switch (static_cast<CTinyUSDValueType>(basety)) {
    case C_TINYUSD_VALUE_UNKNOWN: {
      return 0; // invalid
    }
    case C_TINYUSD_VALUE_BOOL: {
      return 1;
    }
    case C_TINYUSD_VALUE_TOKEN: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_TOKEN_VECTOR: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_STRING: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_STRING_VECTOR: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_HALF: {
      return 1;
    }
    case C_TINYUSD_VALUE_HALF2: {
      return 2;
    }
    case C_TINYUSD_VALUE_HALF3: {
      return 3;
    }
    case C_TINYUSD_VALUE_HALF4: {
      return 4;
    }
    case C_TINYUSD_VALUE_INT: {
      return 1;
    }
    case C_TINYUSD_VALUE_INT2: {
      return 2;
    }
    case C_TINYUSD_VALUE_INT3: {
      return 3;
    }
    case C_TINYUSD_VALUE_INT4: {
      return 4;
    }
    case C_TINYUSD_VALUE_UINT: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT2: {
      return 2;
    }
    case C_TINYUSD_VALUE_UINT3: {
      return 3;
    }
    case C_TINYUSD_VALUE_UINT4: {
      return 4;
    }
    case C_TINYUSD_VALUE_INT64: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT64: {
      return 1;
    }
    case C_TINYUSD_VALUE_FLOAT: {
      return 1;
    }
    case C_TINYUSD_VALUE_FLOAT2: {
      return 2;
    }
    case C_TINYUSD_VALUE_FLOAT3: {
      return 3;
    }
    case C_TINYUSD_VALUE_FLOAT4: {
      return 4;
    }
    case C_TINYUSD_VALUE_DOUBLE: {
      return 1;
    }
    case C_TINYUSD_VALUE_DOUBLE2: {
      return 2;
    }
    case C_TINYUSD_VALUE_DOUBLE3: {
      return 3;
    }
    case C_TINYUSD_VALUE_DOUBLE4: {
      return 4;
    }
    case C_TINYUSD_VALUE_QUATH: {
      return 4;
    }
    case C_TINYUSD_VALUE_QUATF: {
      return 4;
    }
    case C_TINYUSD_VALUE_QUATD: {
      return 4;
    }
    case C_TINYUSD_VALUE_NORMAL3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_NORMAL3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_NORMAL3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_VECTOR3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_VECTOR3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_VECTOR3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_POINT3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_POINT3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_POINT3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD2H: {
      return 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD2F: {
      return 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD2D: {
      return 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_COLOR3H: {
      return 3;
    }
    case C_TINYUSD_VALUE_COLOR3F: {
      return 3;
    }
    case C_TINYUSD_VALUE_COLOR3D: {
      return 3;
    }
    case C_TINYUSD_VALUE_COLOR4H: {
      return 4;
    }
    case C_TINYUSD_VALUE_COLOR4F: {
      return 4;
    }
    case C_TINYUSD_VALUE_COLOR4D: {
      return 4;
    }
    case C_TINYUSD_VALUE_MATRIX2D: {
      return 2 * 2;
    }
    case C_TINYUSD_VALUE_MATRIX3D: {
      return 3 * 3;
    }
    case C_TINYUSD_VALUE_MATRIX4D: {
      return 4 * 4;
    }
    case C_TINYUSD_VALUE_FRAME4D: {
      return 4 * 4;
    }
    case C_TINYUSD_VALUE_DICTIONARY: {
      return 0;
    }
    case C_TINYUSD_VALUE_END: {
      return 0;
    }  // invalid
       // default: { return 0; }
  }

  return 0;
}

uint32_t c_tinyusd_value_type_is_numeric(CTinyUSDValueType value_type) {
  // drop array bit.
  uint32_t basety = value_type & (~C_TINYUSD_VALUE_1D_BIT);

  switch (static_cast<CTinyUSDValueType>(basety)) {
    case C_TINYUSD_VALUE_UNKNOWN: {
      return 0;
    }
    case C_TINYUSD_VALUE_BOOL: {
      return 1;
    }
    case C_TINYUSD_VALUE_TOKEN: {
      return 0;
    }
    case C_TINYUSD_VALUE_TOKEN_VECTOR: {
      return 0;
    }
    case C_TINYUSD_VALUE_STRING: {
      return 0;
    }
    case C_TINYUSD_VALUE_STRING_VECTOR: {
      return 0;
    }
    case C_TINYUSD_VALUE_HALF: {
      return 1;
    }
    case C_TINYUSD_VALUE_HALF2: {
      return 1;
    }
    case C_TINYUSD_VALUE_HALF3: {
      return 1;
    }
    case C_TINYUSD_VALUE_HALF4: {
      return 1;
    }
    case C_TINYUSD_VALUE_INT: {
      return 1;
    }
    case C_TINYUSD_VALUE_INT2: {
      return 1;
    }
    case C_TINYUSD_VALUE_INT3: {
      return 1;
    }
    case C_TINYUSD_VALUE_INT4: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT2: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT3: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT4: {
      return 1;
    }
    case C_TINYUSD_VALUE_INT64: {
      return 1;
    }
    case C_TINYUSD_VALUE_UINT64: {
      return 1;
    }
    case C_TINYUSD_VALUE_FLOAT: {
      return 1;
    }
    case C_TINYUSD_VALUE_FLOAT2: {
      return 1;
    }
    case C_TINYUSD_VALUE_FLOAT3: {
      return 1;
    }
    case C_TINYUSD_VALUE_FLOAT4: {
      return 1;
    }
    case C_TINYUSD_VALUE_DOUBLE: {
      return 1;
    }
    case C_TINYUSD_VALUE_DOUBLE2: {
      return 1;
    }
    case C_TINYUSD_VALUE_DOUBLE3: {
      return 1;
    }
    case C_TINYUSD_VALUE_DOUBLE4: {
      return 1;
    }
    case C_TINYUSD_VALUE_QUATH: {
      return 1;
    }
    case C_TINYUSD_VALUE_QUATF: {
      return 1;
    }
    case C_TINYUSD_VALUE_QUATD: {
      return 1;
    }
    case C_TINYUSD_VALUE_NORMAL3H: {
      return 1;
    }
    case C_TINYUSD_VALUE_NORMAL3F: {
      return 1;
    }
    case C_TINYUSD_VALUE_NORMAL3D: {
      return 1;
    }
    case C_TINYUSD_VALUE_VECTOR3H: {
      return 1;
    }
    case C_TINYUSD_VALUE_VECTOR3F: {
      return 1;
    }
    case C_TINYUSD_VALUE_VECTOR3D: {
      return 1;
    }
    case C_TINYUSD_VALUE_POINT3H: {
      return 1;
    }
    case C_TINYUSD_VALUE_POINT3F: {
      return 1;
    }
    case C_TINYUSD_VALUE_POINT3D: {
      return 1;
    }
    case C_TINYUSD_VALUE_TEXCOORD2H: {
      return 1;
    }
    case C_TINYUSD_VALUE_TEXCOORD2F: {
      return 1;
    }
    case C_TINYUSD_VALUE_TEXCOORD2D: {
      return 1;
    }
    case C_TINYUSD_VALUE_TEXCOORD3H: {
      return 1;
    }
    case C_TINYUSD_VALUE_TEXCOORD3F: {
      return 1;
    }
    case C_TINYUSD_VALUE_TEXCOORD3D: {
      return 1;
    }
    case C_TINYUSD_VALUE_COLOR3H: {
      return 1;
    }
    case C_TINYUSD_VALUE_COLOR3F: {
      return 1;
    }
    case C_TINYUSD_VALUE_COLOR3D: {
      return 1;
    }
    case C_TINYUSD_VALUE_COLOR4H: {
      return 1;
    }
    case C_TINYUSD_VALUE_COLOR4F: {
      return 1;
    }
    case C_TINYUSD_VALUE_COLOR4D: {
      return 1;
    }
    case C_TINYUSD_VALUE_MATRIX2D: {
      return 1;
    }
    case C_TINYUSD_VALUE_MATRIX3D: {
      return 1;
    }
    case C_TINYUSD_VALUE_MATRIX4D: {
      return 1;
    }
    case C_TINYUSD_VALUE_FRAME4D: {
      return 1;
    }
    case C_TINYUSD_VALUE_DICTIONARY: {
      return 0;
    }
    case C_TINYUSD_VALUE_END: {
      return 0;
    }  // invalid
       // default: { return 0; }
  }

  return 0;
}

uint32_t c_tinyusd_value_type_sizeof(CTinyUSDValueType value_type) {
  // drop array bit.
  uint32_t basety = value_type & (~C_TINYUSD_VALUE_1D_BIT);

  switch (static_cast<CTinyUSDValueType>(basety)) {
    case C_TINYUSD_VALUE_UNKNOWN: {
      return 0;
    }
    case C_TINYUSD_VALUE_BOOL: {
      return 1;
    }
    case C_TINYUSD_VALUE_TOKEN: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_TOKEN_VECTOR: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_STRING: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_STRING_VECTOR: {
      return 0;
    }  // invalid
    case C_TINYUSD_VALUE_HALF: {
      return sizeof(uint16_t);
    }
    case C_TINYUSD_VALUE_HALF2: {
      return sizeof(uint16_t) * 2;
    }
    case C_TINYUSD_VALUE_HALF3: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_HALF4: {
      return sizeof(uint16_t) * 4;
    }
    case C_TINYUSD_VALUE_INT: {
      return sizeof(int);
    }
    case C_TINYUSD_VALUE_INT2: {
      return sizeof(int) * 2;
    }
    case C_TINYUSD_VALUE_INT3: {
      return sizeof(int) * 3;
    }
    case C_TINYUSD_VALUE_INT4: {
      return sizeof(int) * 4;
    }
    case C_TINYUSD_VALUE_UINT: {
      return sizeof(uint32_t);
    }
    case C_TINYUSD_VALUE_UINT2: {
      return sizeof(uint32_t) * 2;
    }
    case C_TINYUSD_VALUE_UINT3: {
      return sizeof(uint32_t) * 3;
    }
    case C_TINYUSD_VALUE_UINT4: {
      return sizeof(uint32_t) * 4;
    }
    case C_TINYUSD_VALUE_INT64: {
      return sizeof(int64_t);
    }
    case C_TINYUSD_VALUE_UINT64: {
      return sizeof(uint64_t);
    }
    case C_TINYUSD_VALUE_FLOAT: {
      return sizeof(float);
    }
    case C_TINYUSD_VALUE_FLOAT2: {
      return sizeof(float) * 2;
    }
    case C_TINYUSD_VALUE_FLOAT3: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_FLOAT4: {
      return sizeof(float) * 4;
    }
    case C_TINYUSD_VALUE_DOUBLE: {
      return sizeof(double);
    }
    case C_TINYUSD_VALUE_DOUBLE2: {
      return sizeof(double) * 2;
    }
    case C_TINYUSD_VALUE_DOUBLE3: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_DOUBLE4: {
      return sizeof(double) * 4;
    }
    case C_TINYUSD_VALUE_QUATH: {
      return sizeof(uint16_t) * 4;
    }
    case C_TINYUSD_VALUE_QUATF: {
      return sizeof(float) * 4;
    }
    case C_TINYUSD_VALUE_QUATD: {
      return sizeof(double) * 4;
    }
    case C_TINYUSD_VALUE_NORMAL3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_NORMAL3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_NORMAL3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_VECTOR3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_VECTOR3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_VECTOR3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_POINT3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_POINT3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_POINT3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD2H: {
      return sizeof(uint16_t) * 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD2F: {
      return sizeof(float) * 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD2D: {
      return sizeof(double) * 2;
    }
    case C_TINYUSD_VALUE_TEXCOORD3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_TEXCOORD3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_COLOR3H: {
      return sizeof(uint16_t) * 3;
    }
    case C_TINYUSD_VALUE_COLOR3F: {
      return sizeof(float) * 3;
    }
    case C_TINYUSD_VALUE_COLOR3D: {
      return sizeof(double) * 3;
    }
    case C_TINYUSD_VALUE_COLOR4H: {
      return sizeof(uint16_t) * 4;
    }
    case C_TINYUSD_VALUE_COLOR4F: {
      return sizeof(float) * 4;
    }
    case C_TINYUSD_VALUE_COLOR4D: {
      return sizeof(double) * 4;
    }
    case C_TINYUSD_VALUE_MATRIX2D: {
      return sizeof(double) * 2 * 2;
    }
    case C_TINYUSD_VALUE_MATRIX3D: {
      return sizeof(double) * 3 * 3;
    }
    case C_TINYUSD_VALUE_MATRIX4D: {
      return sizeof(double) * 4 * 4;
    }
    case C_TINYUSD_VALUE_FRAME4D: {
      return sizeof(double) * 4 * 4;
    }
    case C_TINYUSD_VALUE_DICTIONARY: {
      return 0;
    }
    case C_TINYUSD_VALUE_END: {
      return 0;
    }  // invalid
       // default: { return 0; }
  }

  return 0;
}

CTinyUSDFormat c_tinyusd_detect_format(const char *filename) {
  if (tinyusdz::IsUSDA(filename)) {
    return C_TINYUSD_FORMAT_USDA;
  }

  if (tinyusdz::IsUSDC(filename)) {
    return C_TINYUSD_FORMAT_USDC;
  }

  if (tinyusdz::IsUSDZ(filename)) {
    return C_TINYUSD_FORMAT_USDZ;
  }

  return C_TINYUSD_FORMAT_UNKNOWN;
}

const char *c_tinyusd_prim_type_name(CTinyUSDPrimType prim_type) {
  // 32 should be enough length to support all C_TINYUSD_PRIM_*** type
  static thread_local char buf[32];

  const char *tyname = "";

  switch (prim_type) {
    case C_TINYUSD_PRIM_UNKNOWN: {
      return nullptr;
    }
    case C_TINYUSD_PRIM_MODEL: {
      // empty string for Model
      tyname = "";
      break;
    }
    case C_TINYUSD_PRIM_SCOPE: {
      tyname = "Scope";
      break;
    }  // empty string for Model
    case C_TINYUSD_PRIM_XFORM: {
      tyname = tinyusdz::kGeomXform;
      break;
    }
    case C_TINYUSD_PRIM_MESH: {
      tyname = tinyusdz::kGeomMesh;
      break;
    }
    case C_TINYUSD_PRIM_GEOMSUBSET: {
      tyname = tinyusdz::kGeomSubset;
      break;
    }
    case C_TINYUSD_PRIM_MATERIAL: {
      tyname = tinyusdz::kMaterial;
      break;
    }
    case C_TINYUSD_PRIM_SHADER: {
      tyname = tinyusdz::kShader;
      break;
    }
    case C_TINYUSD_PRIM_CAMERA: {
      tyname = tinyusdz::kGeomCamera;
      break;
    }
    case C_TINYUSD_PRIM_SPHERE_LIGHT: {
      tyname = tinyusdz::kSphereLight;
      break;
    }
    case C_TINYUSD_PRIM_DISTANT_LIGHT: {
      tyname = tinyusdz::kDistantLight;
      break;
    }
    case C_TINYUSD_PRIM_RECT_LIGHT: {
      tyname = tinyusdz::kRectLight;
      break;
    }
    case C_TINYUSD_PRIM_END: {
      return nullptr;
    }
  }

  size_t sz = strlen(tyname);
  if (sz > 31) {
    // Just in case: this should not happen though.
    sz = 31;
  }
  strncpy(buf, tyname, sz);
  buf[sz] = '\0';

  return buf;
}

CTinyUSDPrimType c_tinyusd_prim_type_from_string(const char *c_type_name) {
  std::string type_name(c_type_name);

  if (type_name == "Model") {
    return C_TINYUSD_PRIM_MODEL;
  } else if (type_name == "Scope") {
    return C_TINYUSD_PRIM_SCOPE;
  } else if (type_name == tinyusdz::kGeomXform) {
    return C_TINYUSD_PRIM_XFORM;
  } else if (type_name == tinyusdz::kGeomMesh) {
    return C_TINYUSD_PRIM_MESH;
  } else if (type_name == tinyusdz::kGeomSubset) {
    return C_TINYUSD_PRIM_GEOMSUBSET;
  } else if (type_name == tinyusdz::kGeomCamera) {
    return C_TINYUSD_PRIM_CAMERA;
  } else if (type_name == tinyusdz::kMaterial) {
    return C_TINYUSD_PRIM_MATERIAL;
  } else if (type_name == tinyusdz::kShader) {
    return C_TINYUSD_PRIM_SHADER;
  } else if (type_name == tinyusdz::kSphereLight) {
    return C_TINYUSD_PRIM_SPHERE_LIGHT;
  } else if (type_name == tinyusdz::kDistantLight) {
    return C_TINYUSD_PRIM_DISTANT_LIGHT;
  } else if (type_name == tinyusdz::kRectLight) {
    return C_TINYUSD_PRIM_RECT_LIGHT;
  } else {
    return C_TINYUSD_PRIM_UNKNOWN;
  }
}

const char *c_tinyusd_prim_element_name(
    const CTinyUSDPrim *prim) {

  if (!prim) {
    return nullptr;
  }

  const tinyusdz::Prim *p = reinterpret_cast<const tinyusdz::Prim *>(prim);
  return p->element_name().c_str();
}

int c_tinyusd_prim_append_child(CTinyUSDPrim *prim, CTinyUSDPrim *child_prim) {
  std::cout << "C: Append child: " << prim << "," << child_prim << "\n";
  DCOUT("DCOUT: Append child: " << prim << ", " << child_prim);

  if (!prim) {
    DCOUT("`prim` is nullptr.");
    return 0;
  }

  if (!child_prim) {
    DCOUT("`child_prim` is nullptr.");
    return 0;
  }

  tinyusdz::Prim *pprim = reinterpret_cast<tinyusdz::Prim *>(prim);
  tinyusdz::Prim *pchild = reinterpret_cast<tinyusdz::Prim *>(child_prim);

  pprim->children().emplace_back(*pchild);

  return 1;
}

int c_tinyusd_prim_append_child_move(CTinyUSDPrim *prim, CTinyUSDPrim *child_prim) {
  if (!prim) {
    return 0;
  }

  if (!child_prim) {
    return 0;
  }

  tinyusdz::Prim *pprim = reinterpret_cast<tinyusdz::Prim *>(prim);
  tinyusdz::Prim *pchild = reinterpret_cast<tinyusdz::Prim *>(child_prim);

  pprim->children().emplace_back(std::move(*pchild));

  return 1;
}

uint64_t c_tinyusd_prim_num_children(const CTinyUSDPrim *prim) {
  if (!prim) {
    return 0;
  }

  const tinyusdz::Prim *pprim = reinterpret_cast<const tinyusdz::Prim *>(prim);
  return pprim->children().size();
}

const char *c_tinyusd_prim_type(const CTinyUSDPrim *prim) {
  if (!prim) {
    return nullptr;
  }

  const tinyusdz::Prim *pprim = reinterpret_cast<const tinyusdz::Prim *>(prim);

  return pprim->prim_type_name().c_str();
}


int c_tinyusd_prim_get_child(const CTinyUSDPrim *prim,
                                              uint64_t child_index,
                                              const CTinyUSDPrim ** child_prim) {
  if (!prim) {
    return 0;
  }

  const tinyusdz::Prim *pprim = reinterpret_cast<const tinyusdz::Prim *>(prim);
  if (child_index >= pprim->children().size()) {
    return 0;
  }

  const tinyusdz::Prim *pchild = &pprim->children()[size_t(child_index)];

  (*child_prim) = reinterpret_cast<const CTinyUSDPrim *>(pchild);

  return 1;
}

static bool c_tinyusd_find_prim_property(const tinyusdz::Prim *pprim,
                                         const char *prop_name,
                                         tinyusdz::Property *prop) {
  if (!pprim || !prop_name || !prop) {
    return false;
  }

  std::string prop_name_str(prop_name);
  std::string err;
  if (tinyusdz::tydra::GetProperty(*pprim, prop_name_str, prop, &err)) {
    return true;
  }

  auto try_props_map = [&](const auto &typed_prim) -> bool {
    const auto it = typed_prim.props.find(prop_name_str);
    if (it == typed_prim.props.end()) {
      return false;
    }

    (*prop) = it->second;
    return true;
  };

  if (pprim->is<tinyusdz::Model>()) {
    return try_props_map(*pprim->as<tinyusdz::Model>());
  } else if (pprim->is<tinyusdz::Xform>()) {
    return try_props_map(*pprim->as<tinyusdz::Xform>());
  } else if (pprim->is<tinyusdz::Scope>()) {
    return try_props_map(*pprim->as<tinyusdz::Scope>());
  } else if (pprim->is<tinyusdz::GeomMesh>()) {
    return try_props_map(*pprim->as<tinyusdz::GeomMesh>());
  } else if (pprim->is<tinyusdz::GeomSubset>()) {
    return try_props_map(*pprim->as<tinyusdz::GeomSubset>());
  } else if (pprim->is<tinyusdz::GeomCamera>()) {
    return try_props_map(*pprim->as<tinyusdz::GeomCamera>());
  } else if (pprim->is<tinyusdz::Shader>()) {
    return try_props_map(*pprim->as<tinyusdz::Shader>());
  } else if (pprim->is<tinyusdz::Material>()) {
    return try_props_map(*pprim->as<tinyusdz::Material>());
  } else if (pprim->is<tinyusdz::SkelRoot>()) {
    return try_props_map(*pprim->as<tinyusdz::SkelRoot>());
  } else if (pprim->is<tinyusdz::BlendShape>()) {
    return try_props_map(*pprim->as<tinyusdz::BlendShape>());
  } else if (pprim->is<tinyusdz::Skeleton>()) {
    return try_props_map(*pprim->as<tinyusdz::Skeleton>());
  } else if (pprim->is<tinyusdz::SkelAnimation>()) {
    return try_props_map(*pprim->as<tinyusdz::SkelAnimation>());
  } else if (pprim->is<tinyusdz::SphereLight>()) {
    return try_props_map(*pprim->as<tinyusdz::SphereLight>());
  } else if (pprim->is<tinyusdz::CylinderLight>()) {
    return try_props_map(*pprim->as<tinyusdz::CylinderLight>());
  } else if (pprim->is<tinyusdz::RectLight>()) {
    return try_props_map(*pprim->as<tinyusdz::RectLight>());
  } else if (pprim->is<tinyusdz::DiskLight>()) {
    return try_props_map(*pprim->as<tinyusdz::DiskLight>());
  } else if (pprim->is<tinyusdz::DistantLight>()) {
    return try_props_map(*pprim->as<tinyusdz::DistantLight>());
  } else if (pprim->is<tinyusdz::DomeLight>()) {
    return try_props_map(*pprim->as<tinyusdz::DomeLight>());
  } else if (pprim->is<tinyusdz::GeometryLight>()) {
    return try_props_map(*pprim->as<tinyusdz::GeometryLight>());
  } else if (pprim->is<tinyusdz::PortalLight>()) {
    return try_props_map(*pprim->as<tinyusdz::PortalLight>());
  }

  return false;
}

struct c_tinyusd_schema_property_info {
  std::string object_kind;
  std::string type_name;
  std::string default_text;
  std::string variability;
};

static bool c_tinyusd_try_get_schema_property_info(
    const tinyusdz::Prim *pprim,
    const std::string &prop_name,
    c_tinyusd_schema_property_info *info) {
  if (!pprim || !info) {
    return false;
  }

  auto set_attr = [&](const std::string &type_name,
                      const std::string &default_text,
                      const std::string &variability = "varying") {
    info->object_kind = "attribute";
    info->type_name = type_name;
    info->default_text = default_text;
    info->variability = variability;
    return true;
  };

  auto set_light_common = [&]() {
    if (prop_name == "inputs:color") return set_attr("color3f", "(1, 1, 1)");
    if (prop_name == "inputs:colorTemperature") return set_attr("float", "6500");
    if (prop_name == "inputs:diffuse") return set_attr("float", "1");
    if (prop_name == "inputs:enableColorTemperature") return set_attr("bool", "false");
    if (prop_name == "inputs:exposure") return set_attr("float", "0");
    if (prop_name == "inputs:intensity") return set_attr("float", "1");
    if (prop_name == "inputs:normalize") return set_attr("bool", "false");
    if (prop_name == "inputs:specular") return set_attr("float", "1");
    return false;
  };

  if (pprim->is<tinyusdz::GeomCamera>()) {
    if (prop_name == "projection") return set_attr("token", "perspective");
    if (prop_name == "focalLength") return set_attr("float", "50");
    if (prop_name == "horizontalAperture") return set_attr("float", "20.965");
    if (prop_name == "verticalAperture") return set_attr("float", "15.2908");
    if (prop_name == "horizontalApertureOffset") return set_attr("float", "0");
    if (prop_name == "verticalApertureOffset") return set_attr("float", "0");
    if (prop_name == "clippingRange") return set_attr("float2", "(0.1, 1000000)");
    if (prop_name == "exposure") return set_attr("float", "0");
    if (prop_name == "focusDistance") return set_attr("float", "0");
    if (prop_name == "fStop") return set_attr("float", "0");
    if (prop_name == "stereoRole") return set_attr("token", "mono", "uniform");
    if (prop_name == "shutterOpen") return set_attr("double", "0");
    if (prop_name == "shutterClose") return set_attr("double", "0");
  }

  if (pprim->is<tinyusdz::GeomMesh>()) {
    if (prop_name == "doubleSided") return set_attr("bool", "false", "uniform");
  }

  if (pprim->is<tinyusdz::SphereLight>()) {
    if (set_light_common()) return true;
    if (prop_name == "inputs:radius") return set_attr("float", "0.5");
  }

  if (pprim->is<tinyusdz::CylinderLight>()) {
    if (set_light_common()) return true;
    if (prop_name == "inputs:length") return set_attr("float", "1");
    if (prop_name == "inputs:radius") return set_attr("float", "0.5");
  }

  if (pprim->is<tinyusdz::RectLight>()) {
    if (set_light_common()) return true;
    if (prop_name == "inputs:height") return set_attr("float", "1");
    if (prop_name == "inputs:width") return set_attr("float", "1");
  }

  if (pprim->is<tinyusdz::DiskLight>()) {
    if (set_light_common()) return true;
    if (prop_name == "inputs:radius") return set_attr("float", "0.5");
  }

  if (pprim->is<tinyusdz::DistantLight>()) {
    if (set_light_common()) return true;
    if (prop_name == "inputs:angle") return set_attr("float", "0.53");
  }

  if (pprim->is<tinyusdz::DomeLight>()) {
    if (set_light_common()) return true;
    if (prop_name == "guideRadius") return set_attr("float", "100000");
    if (prop_name == "inputs:texture:format") return set_attr("token", "automatic");
  }

  return false;
}

int c_tinyusd_prim_property_get_value(const CTinyUSDPrim *prim,
                                      const char *prop_name,
                                      const CTinyUSDValue **value) {
  if (!prim) {
    return 0;
  }

  if (!prop_name) {
    return 0;
  }

  if (!value) {
    return 0;
  }

  const tinyusdz::Prim *pprim = reinterpret_cast<const tinyusdz::Prim *>(prim);

  tinyusdz::Property prop;
  if (!c_tinyusd_find_prim_property(pprim, prop_name, &prop)) {
    return 0;
  }

  if (!prop.is_attribute()) {
    return 0;
  }

  const tinyusdz::Attribute &attr = prop.get_attribute();
  if (!attr.is_value()) {
    return 0;
  }

  static thread_local tinyusdz::value::Value *local_value = nullptr;
  if (!local_value) {
    local_value = new tinyusdz::value::Value(nullptr);
  }

  (*local_value) = attr.get_var().value_raw();
  (*value) = reinterpret_cast<const CTinyUSDValue *>(local_value);

  return 1;
}

int c_tinyusd_prim_property_get_type_name(const CTinyUSDPrim *prim,
                                          const char *prop_name,
                                          c_tinyusd_string_t *type_name_out) {
  if (!prim || !prop_name || !type_name_out) {
    return 0;
  }

  const tinyusdz::Prim *pprim = reinterpret_cast<const tinyusdz::Prim *>(prim);
  tinyusdz::Property prop;
  if (!c_tinyusd_find_prim_property(pprim, prop_name, &prop)) {
    c_tinyusd_schema_property_info info;
    if (!c_tinyusd_try_get_schema_property_info(pprim, prop_name, &info)) {
      return 0;
    }
    return c_tinyusd_string_replace(type_name_out, info.type_name.c_str());
  }

  std::string type_name = prop.value_type_name();
  if (type_name.empty()) {
    if (prop.is_relationship()) {
      type_name = "relationship";
    } else if (prop.is_attribute_connection()) {
      type_name = "connection";
    } else if (prop.is_attribute()) {
      type_name = "attribute";
    } else {
      type_name = "unknown";
    }
  }

  return c_tinyusd_string_replace(type_name_out, type_name.c_str());
}

int c_tinyusd_prim_property_to_string(const CTinyUSDPrim *prim,
                                      const char *prop_name,
                                      c_tinyusd_string_t *text_out) {
  if (!prim || !prop_name || !text_out) {
    return 0;
  }

  const tinyusdz::Prim *pprim = reinterpret_cast<const tinyusdz::Prim *>(prim);
  tinyusdz::Property prop;
  if (!c_tinyusd_find_prim_property(pprim, prop_name, &prop)) {
    c_tinyusd_schema_property_info info;
    if (!c_tinyusd_try_get_schema_property_info(pprim, prop_name, &info)) {
      return 0;
    }
    return c_tinyusd_string_replace(text_out, info.default_text.c_str());
  }

  std::string text;

  if (prop.is_attribute()) {
    const tinyusdz::Attribute &attr = prop.get_attribute();
    if (attr.is_value()) {
      text = tinyusdz::value::pprint_value(attr.get_var().value_raw(), 0, false);
    } else if (attr.is_connection()) {
      const auto &connections = attr.connections();
      text = "connect=[";
      for (size_t i = 0; i < connections.size(); i++) {
        if (i > 0) {
          text += ", ";
        }
        text += connections[i].full_path_name();
      }
      text += "]";
    } else if (attr.is_timesamples()) {
      text = "[timesamples]";
    } else if (attr.is_blocked()) {
      text = "[blocked]";
    } else {
      text = "[attribute]";
    }
  } else if (prop.is_relationship()) {
    std::vector<tinyusdz::Path> targets = prop.get_relationTargets();
    text = "rel=[";
    for (size_t i = 0; i < targets.size(); i++) {
      if (i > 0) {
        text += ", ";
      }
      text += targets[i].full_path_name();
    }
    text += "]";
  } else {
    text = "[property]";
  }

  return c_tinyusd_string_replace(text_out, text.c_str());
}

int c_tinyusd_prim_property_metadata_to_string(const CTinyUSDPrim *prim,
                                               const char *prop_name,
                                               c_tinyusd_string_t *text_out) {
  if (!prim || !prop_name || !text_out) {
    return 0;
  }

  const tinyusdz::Prim *pprim = reinterpret_cast<const tinyusdz::Prim *>(prim);
  tinyusdz::Property prop;
  const bool found_prop = c_tinyusd_find_prim_property(pprim, prop_name, &prop);
  c_tinyusd_schema_property_info schema_info;
  const bool found_schema = c_tinyusd_try_get_schema_property_info(pprim, prop_name, &schema_info);

  if (!found_prop && !found_schema) {
    return 0;
  }

  std::string text;
  const std::string prim_path = pprim->element_path().full_path_name();
  const std::string property_path = prim_path + "." + std::string(prop_name);

  auto append_line = [&](const std::string &key, const std::string &value) {
    text += key;
    text += " = ";
    text += value;
    text += "\n";
  };

  if (found_prop && prop.is_attribute()) {
    const tinyusdz::Attribute &attr = prop.get_attribute();
    append_line("object", "attribute");
    append_line("path", property_path);

    std::string type_name = attr.type_name();
    if (type_name.empty()) {
      type_name = prop.value_type_name();
    }
    if (type_name.empty()) {
      type_name = "unknown";
    }
    append_line("type", type_name);
    append_line("variability", tinyusdz::to_string(attr.variability()));

    if (attr.is_value()) {
      append_line("default", tinyusdz::value::pprint_value(attr.get_var().value_raw(), 0, false));
    } else if (attr.is_connection()) {
      const auto &connections = attr.connections();
      std::string conn = "[";
      for (size_t i = 0; i < connections.size(); i++) {
        if (i > 0) {
          conn += ", ";
        }
        conn += connections[i].full_path_name();
      }
      conn += "]";
      append_line("default", "connect=" + conn);
    } else if (attr.is_timesamples()) {
      append_line("default", "[timesamples]");
    } else if (attr.is_blocked()) {
      append_line("default", "[blocked]");
    } else {
      append_line("default", "[not-authored]");
    }

    const tinyusdz::AttrMeta &meta = attr.metas();
    append_line("authoredMetadata", meta.authored() ? "true" : "false");
    if (meta.authored()) {
      text += tinyusdz::print_attr_metas(meta, 0);
    }
  } else if (found_prop && prop.is_relationship()) {
    append_line("object", "relationship");
    append_line("path", property_path);
    append_line("type", "relationship");

    std::vector<tinyusdz::Path> targets = prop.get_relationTargets();
    std::string rel = "[";
    for (size_t i = 0; i < targets.size(); i++) {
      if (i > 0) {
        rel += ", ";
      }
      rel += targets[i].full_path_name();
    }
    rel += "]";
    append_line("default", rel);

    const tinyusdz::AttrMeta &meta = prop.get_relationship().metas();
    append_line("authoredMetadata", meta.authored() ? "true" : "false");
    if (meta.authored()) {
      text += tinyusdz::print_attr_metas(meta, 0);
    }
  } else if (found_schema) {
    append_line("object", schema_info.object_kind);
    append_line("path", property_path);
    append_line("type", schema_info.type_name);
    append_line("variability", schema_info.variability);
    append_line("default", schema_info.default_text);
    append_line("authoredMetadata", "false");
  } else {
    append_line("object", "property");
    append_line("path", property_path);
    append_line("type", "unknown");
    append_line("default", "[unavailable]");
    append_line("authoredMetadata", "false");
  }

  return c_tinyusd_string_replace(text_out, text.c_str());
}

int c_tinyusd_prim_del_child(CTinyUSDPrim *prim, uint64_t child_idx) {
  if (!prim) {
    return 0;
  }

  tinyusdz::Prim *pprim = reinterpret_cast<tinyusdz::Prim *>(prim);
  if (child_idx >= pprim->children().size()) {
    return 0;
  }

  pprim->children().erase(pprim->children().begin() + ptrdiff_t(child_idx));

  return 1;
}

c_tinyusd_token_t *c_tinyusd_token_new(const char *str) {
  if (!str) {
    return nullptr;
  }

  auto *value = new tinyusdz::value::token(str);

  return reinterpret_cast<c_tinyusd_token_t *>(value);
}

c_tinyusd_token_t *c_tinyusd_token_dup(const c_tinyusd_token_t *_tok) {

  if (!_tok) {
    return nullptr;
  }

  auto *tok = reinterpret_cast<const tinyusdz::value::token *>(_tok);

  auto *value = new tinyusdz::value::token(tok->str());

  return reinterpret_cast<c_tinyusd_token_t *>(value);
}

int c_tinyusd_token_free(c_tinyusd_token_t *tok) {
  if (!tok) {
    return 0;
  }

  auto *p = reinterpret_cast<tinyusdz::value::token *>(tok);
  delete p;

  return 1;  // ok
}

const char *c_tinyusd_token_str(const c_tinyusd_token_t *tok) {
  if (!tok) {
    return nullptr;
  }

  auto *p = reinterpret_cast<const tinyusdz::value::token *>(tok);
  return p->str().c_str();
}

size_t c_tinyusd_token_size(const c_tinyusd_token_t *tok) {
  if (!tok) {
    return 0;
  }

  auto *p = reinterpret_cast<const tinyusdz::value::token *>(tok);

  return p->str().size();
}

c_tinyusd_token_vector_t *c_tinyusd_token_vector_new_empty() {

  auto *value = new std::vector<tinyusdz::value::token>();
  return reinterpret_cast<c_tinyusd_token_vector_t *>(value);
}

c_tinyusd_token_vector_t *c_tinyusd_token_vector_new(const size_t n, const char **strs) {

  if (strs) {
    for (size_t i = 0; i < n; i++) {
      if (!strs[i]) {
        return nullptr;
      }
    }

    auto *value = new std::vector<tinyusdz::value::token>(n);
    for (size_t i = 0; i < n; i++) {
      value->at(i) = tinyusdz::value::token(strs[i]);
    }
    return reinterpret_cast<c_tinyusd_token_vector_t *>(value);
  } else {
    auto *value = new std::vector<tinyusdz::value::token>(n);
    return reinterpret_cast<c_tinyusd_token_vector_t *>(value);
  }
}

size_t c_tinyusd_token_vector_size(const c_tinyusd_token_vector_t *sv) {
  if (!sv) {
    return 0;
  }

  auto *p = reinterpret_cast<const std::vector<tinyusdz::value::token> *>(sv);

  return p->size();
}

int c_tinyusd_token_vector_clear(c_tinyusd_token_vector_t *sv) {
  if (!sv) {
    return 0;
  }

  auto *p = reinterpret_cast<std::vector<tinyusdz::value::token> *>(sv);
  p->clear();

  return 1;
}

int c_tinyusd_token_vector_resize(c_tinyusd_token_vector_t *sv, const size_t n) {
  if (!sv) {
    return 0;
  }

  auto *p = reinterpret_cast<std::vector<tinyusdz::value::token> *>(sv);

  p->resize(n);

  return 1;
}

int c_tinyusd_token_vector_replace(c_tinyusd_token_vector_t *sv, const size_t idx, const char *str) {
  if (!sv) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  std::vector<tinyusdz::value::token> *pv = reinterpret_cast<std::vector<tinyusdz::value::token> *>(sv);
  if (idx >= pv->size()) {
    return 0;
  }

  pv->at(idx) = tinyusdz::value::token(str);

  return 1;  // ok
}

int c_tinyusd_token_vector_free(c_tinyusd_token_vector_t *sv) {
  if (!sv) {
    return 0;
  }

  auto *p = reinterpret_cast<std::vector<tinyusdz::value::token> *>(sv);
  delete p;

  return 1;  // ok
}

const char *c_tinyusd_token_vector_str(const c_tinyusd_token_vector_t *sv, const size_t idx) {
  if (!sv) {
    return nullptr;
  }

  auto *p = reinterpret_cast<const std::vector<tinyusdz::value::token> *>(sv);
  if (idx >= p->size()) {
    return nullptr;
  }

  return p->at(idx).str().c_str();
}

c_tinyusd_string_t *c_tinyusd_string_new_empty() {

  auto *value = new std::string();

  return reinterpret_cast<c_tinyusd_string_t *>(value);
}

c_tinyusd_string_t *c_tinyusd_string_new(const char *str) {

  if (str) {
    auto *value = new std::string(str);
    return reinterpret_cast<c_tinyusd_string_t *>(value);
  } else {
    auto *value = new std::string();
    return reinterpret_cast<c_tinyusd_string_t *>(value);
  }
}

size_t c_tinyusd_string_size(const c_tinyusd_string_t *s) {
  if (!s) {
    return 0;
  }

  auto *p = reinterpret_cast<const std::string *>(s);

  return p->size();
}

int c_tinyusd_string_replace(c_tinyusd_string_t *s, const char *str) {
  if (!s) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  std::string *p = reinterpret_cast<std::string *>(s);
  (*p) = std::string(str);

  return 1;  // ok
}

int c_tinyusd_string_free(c_tinyusd_string_t *s) {
  if (!s) {
    return 0;
  }

  auto *p = reinterpret_cast<std::string *>(s);
  delete p;

  return 1;  // ok
}

const char *c_tinyusd_string_str(const c_tinyusd_string_t *s) {
  if (!s) {
    return nullptr;
  }

  auto *p = reinterpret_cast<const std::string *>(s);
  return p->c_str();
}

int c_tinyusd_string_vector_new_empty(c_tinyusd_string_vector *sv, const size_t n) {
  if (!sv) {
    return 0;
  }

  auto *value = new std::vector<std::string>(n);
  sv->data = reinterpret_cast<void *>(value);

  return 1;  // ok
}

int c_tinyusd_string_vector_new(c_tinyusd_string_vector *sv, const size_t n, const char **strs) {
  if (!sv) {
    return 0;
  }

  if (strs) {
    auto *value = new std::vector<std::string>(n);
    for (size_t i = 0; i < n; i++) {
      value->at(i) = std::string(strs[i]);
    }
    sv->data = reinterpret_cast<void *>(value);
  } else {
    auto *value = new std::vector<std::string>(n);
    sv->data = reinterpret_cast<void *>(value);
  }

  return 1;  // ok
}

size_t c_tinyusd_string_vector_size(const c_tinyusd_string_vector *sv) {
  if (!sv) {
    return 0;
  }

  if (!sv->data) {
    return 0;
  }

  auto *p = reinterpret_cast<const std::vector<std::string> *>(sv->data);

  return p->size();
}

int c_tinyusd_string_vector_clear(c_tinyusd_string_vector *sv) {
  if (!sv) {
    return 0;
  }

  if (!sv->data) {
    return 0;
  }

  auto *p = reinterpret_cast<std::vector<std::string> *>(sv->data);
  p->clear();

  return 1;
}

int c_tinyusd_string_vector_resize(c_tinyusd_string_vector *sv, const size_t n) {
  if (!sv) {
    return 0;
  }

  if (!sv->data) {
    return 0;
  }

  auto *p = reinterpret_cast<std::vector<std::string> *>(sv->data);

  p->resize(n);

  return 1;
}

int c_tinyusd_string_vector_replace(c_tinyusd_string_vector *sv, const size_t idx, const char *str) {
  if (!sv) {
    return 0;
  }

  if (!sv->data) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  std::vector<std::string> *pv = reinterpret_cast<std::vector<std::string> *>(sv->data);
  if (idx >= pv->size()) {
    return 0;
  }

  pv->at(idx) = std::string(str);

  return 1;  // ok
}

int c_tinyusd_string_vector_free(c_tinyusd_string_vector *sv) {
  if (!sv) {
    return 0;
  }

  if (sv->data) {
    auto *p = reinterpret_cast<std::vector<std::string> *>(sv->data);
    delete p;
    sv->data = nullptr;
  }

  return 1;  // ok
}

const char *c_tinyusd_string_vector_str(const c_tinyusd_string_vector *sv, const size_t idx) {
  if (!sv) {
    return nullptr;
  }

  if (sv->data) {
    auto *p = reinterpret_cast<const std::vector<std::string> *>(sv->data);
    if (idx >= p->size()) {
      return nullptr;
    }

    return p->at(idx).c_str();
  }

  return nullptr;
}


#if 0
int c_tinyusd_buffer_new(CTinyUSDBuffer *buf, CTinyUSDValueType value_type) {
  if (!buf) {
    return 0;
  }

  uint32_t sz = c_tinyusd_value_type_sizeof(value_type);
  if (sz == 0) {
    return 0;
  }

  buf->value_type = value_type;
  buf->ndim = 0;

  //uint8_t *m = new uint8_t[sz];
  //buf->data = reinterpret_cast<void *>(m);
  tinyusdz::value::Value *vp = new tinyusdz::value::Value(); // new `null` Value at the moment
  buf->data = reinterpret_cast<void *>(vp);

  return 1;  // ok
}

int c_tinyusd_buffer_new_and_copy_token(CTinyUSDBuffer *buf, const c_tinyusd_token_t *tok) {
  if (!buf) {
    return 0;
  }

  if (!tok) {
    return 0;
  }

  size_t sz = c_tinyusd_token_size(tok);

  buf->value_type = C_TINYUSD_VALUE_TOKEN;
  buf->ndim = 0;

  if (sz == 0) {
    // Allow null string
    buf->data = nullptr;
  } else {

    const char *str = c_tinyusd_token_str(tok);
    if (strlen(str) != sz) {
      // ???
      return false;
    }

    if (str) {
      uint8_t *m = new uint8_t[sz];

      memcpy(m, str, sz);
      buf->data = reinterpret_cast<void *>(m);
    } else {
      // ???
      return 0;
    }
  }

  return 1;  // ok
}

int c_tinyusd_buffer_new_and_copy_string(CTinyUSDBuffer *buf, const c_tinyusd_string_t *str) {
  if (!buf) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  size_t sz = c_tinyusd_string_size(str);

  buf->value_type = C_TINYUSD_VALUE_STRING;
  buf->ndim = 0;

  if (sz == 0) {
    // Allow null string
    buf->data = nullptr;
  } else {

    const char *s = c_tinyusd_string_str(str);
    if (strlen(s) != sz) {
      // ???
      return false;
    }

    if (s) {
      uint8_t *m = new uint8_t[sz];

      memcpy(m, s, sz);
      buf->data = reinterpret_cast<void *>(m);
    } else {
      // ???
      return 0;
    }
  }

  return 1;  // ok
}

int c_tinyusd_buffer_new_array(CTinyUSDBuffer *buf,
                               CTinyUSDValueType value_type, uint64_t n) {
  if (!buf) {
    return 0;
  }

  uint32_t sz = c_tinyusd_value_type_sizeof(value_type);
  if (sz == 0) {
    return 0;
  }

  buf->value_type = value_type;
  buf->ndim = 1;
  buf->shape[0] = n;

  if (n == 0) {
    // empty array
    buf->data = nullptr;
  } else {
    uint8_t *m = new uint8_t[n * sz];
    buf->data = reinterpret_cast<void *>(m);
  }

  return 1;  // ok
}

int c_tinyusd_buffer_free(CTinyUSDBuffer *buf) {
  if (!buf) {
    return 0;
  }

  if (!buf->data) {
    return 0;
  }

  uint8_t *p = reinterpret_cast<uint8_t *>(buf->data);
  delete[] p;

  buf->data = nullptr;

  return 1;
}
#endif

int c_tinyusd_is_usda_file(const char *filename) {
  if (tinyusdz::IsUSDA(filename)) {
    return 1;
  }
  return 0;
}

int c_tinyusd_is_usdc_file(const char *filename) {
  if (tinyusdz::IsUSDC(filename)) {
    return 1;
  }
  return 0;
}

int c_tinyusd_is_usdz_file(const char *filename) {
  if (tinyusdz::IsUSDZ(filename)) {
    return 1;
  }
  return 0;
}

int c_tinyusd_is_usd_file(const char *filename) {
  if (tinyusdz::IsUSD(filename)) {
    return 1;
  }
  return 0;
}

int c_tinyusd_load_usd_from_file(const char *filename, CTinyUSDStage *stage,
                                 c_tinyusd_string_t *warn,
                                 c_tinyusd_string_t *err) {
  // tinyusdz::Stage *p = new tinyusdz::Stage();

  if (!stage) {
    if (err) {
      c_tinyusd_string_replace(err, "`stage` argument is null.\n");
    }
    return 0;
  }

  std::string _warn;
  std::string _err;

  bool ret = tinyusdz::LoadUSDFromFile(
      filename, reinterpret_cast<tinyusdz::Stage *>(stage), &_warn,
      &_err);

  if (_warn.size() && warn) {
    c_tinyusd_string_replace(warn, _warn.c_str());
  }

  if (!ret) {
    if (err) {
      c_tinyusd_string_replace(err, _err.c_str());
    }

    return 0;
  }

  return 1;
}

int c_tinyusd_load_usda_from_file(const char *filename, CTinyUSDStage *stage,
                                 c_tinyusd_string_t *warn,
                                 c_tinyusd_string_t *err) {
  // tinyusdz::Stage *p = new tinyusdz::Stage();

  if (!stage) {
    if (err) {
      c_tinyusd_string_replace(err, "`stage` argument is null.\n");
    }
    return 0;
  }

  std::string _warn;
  std::string _err;

  bool ret = tinyusdz::LoadUSDAFromFile(
      filename, reinterpret_cast<tinyusdz::Stage *>(stage), &_warn,
      &_err);

  if (_warn.size() && warn) {
    c_tinyusd_string_replace(warn, _warn.c_str());
  }

  if (!ret) {
    if (err) {
      c_tinyusd_string_replace(err, _err.c_str());
    }

    return 0;
  }

  return 1;
}

int c_tinyusd_load_usdc_from_file(const char *filename, CTinyUSDStage *stage,
                                 c_tinyusd_string_t *warn,
                                 c_tinyusd_string_t *err) {
  // tinyusdz::Stage *p = new tinyusdz::Stage();

  if (!stage) {
    if (err) {
      c_tinyusd_string_replace(err, "`stage` argument is null.\n");
    }
    return 0;
  }

  std::string _warn;
  std::string _err;

  bool ret = tinyusdz::LoadUSDCFromFile(
      filename, reinterpret_cast<tinyusdz::Stage *>(stage), &_warn,
      &_err);

  if (_warn.size() && warn) {
    c_tinyusd_string_replace(warn, _warn.c_str());
  }

  if (!ret) {
    if (err) {
      c_tinyusd_string_replace(err, _err.c_str());
    }

    return 0;
  }

  return 1;
}

int c_tinyusd_load_usdz_from_file(const char *filename, CTinyUSDStage *stage,
                                 c_tinyusd_string_t *warn,
                                 c_tinyusd_string_t *err) {
  // tinyusdz::Stage *p = new tinyusdz::Stage();

  if (!stage) {
    if (err) {
      c_tinyusd_string_replace(err, "`stage` argument is null.\n");
    }
    return 0;
  }

  std::string _warn;
  std::string _err;

  bool ret = tinyusdz::LoadUSDZFromFile(
      filename, reinterpret_cast<tinyusdz::Stage *>(stage), &_warn,
      &_err);

  if (_warn.size() && warn) {
    c_tinyusd_string_replace(warn, _warn.c_str());
  }

  if (!ret) {
    if (err) {
      c_tinyusd_string_replace(err, _err.c_str());
    }

    return 0;
  }

  return 1;
}

namespace {

using namespace tinyusdz;

bool CVisitPrimFunction(const Path &abs_path, const Prim &prim,
                        const int32_t tree_depth, void *userdata,
                        std::string *err) {
  (void)tree_depth;

  if (!userdata) {
    if (err) {
      (*err) += "`userdata` is nullptr.\n";
    }
    return false;
  }

  CTinyUSDPrim *pprim = reinterpret_cast<CTinyUSDPrim *>(const_cast<Prim *>(&prim));

  CTinyUSDPath *ppath = reinterpret_cast<CTinyUSDPath *>(const_cast<Path *>(&abs_path));

  CTinyUSDTraversalFunction callback_fun =
      reinterpret_cast<CTinyUSDTraversalFunction>(userdata);

  int ret = callback_fun(pprim, ppath);

  if (ret) {
    return true;
  }

  return false;
}

}  // namespace

CTinyUSDPrim *c_tinyusd_prim_new(const char *_prim_type, c_tinyusd_string_t *err) {

  if (!_prim_type) {
    if (err) {
      c_tinyusd_string_replace(err, "prim_type is nullptr.");
    }
    return nullptr;
  }

  std::string prim_type_name = std::string(_prim_type);
  if (!tinyusdz::isValidIdentifier(prim_type_name)) {
    if (err) {
      c_tinyusd_string_replace(err, "prim_type contains invalid character.");
    }
    return nullptr;
  }

  bool non_builtin_prim_type{false};

  CTinyUSDPrimType prim_type = c_tinyusd_prim_type_from_string(_prim_type);
  if (prim_type == C_TINYUSD_PRIM_UNKNOWN) {
    // Use `Model`
    prim_type = C_TINYUSD_PRIM_MODEL;
    non_builtin_prim_type = true;
  }

  Prim *p{nullptr};

  if (non_builtin_prim_type) {
    Model model;
    model.prim_type_name = std::string(_prim_type);
    p = new Prim(model);
  } else {

#define NEW_PRIM(__cty, __ty) \
    if (prim_type == __cty) {   \
      __ty content;             \
      p = new Prim(content);    \
    } else

    NEW_PRIM(C_TINYUSD_PRIM_XFORM, Xform)
    NEW_PRIM(C_TINYUSD_PRIM_SCOPE, Scope)
    NEW_PRIM(C_TINYUSD_PRIM_MESH, GeomMesh)
    NEW_PRIM(C_TINYUSD_PRIM_GEOMSUBSET, GeomSubset)
    NEW_PRIM(C_TINYUSD_PRIM_MATERIAL, Material)
    NEW_PRIM(C_TINYUSD_PRIM_SHADER, Shader)
    // TODO: More types.
    {
      if (err) {
        std::string msg = "Unknown or unsupported type: " + std::string(_prim_type) + "\n";
        c_tinyusd_string_replace(err, msg.c_str());
      }

      // Unknown or unsupported type.
      DCOUT("Unknown or unsupported type: " << _prim_type);
      return nullptr;
    }
  }

#undef NEW_PRIM

  return reinterpret_cast<CTinyUSDPrim*>(p);
}

CTinyUSDPrim *c_tinyusd_prim_new_builtin(CTinyUSDPrimType prim_type) {

  const char *prim_type_name = c_tinyusd_prim_type_name(prim_type);
  if (!prim_type_name) {
    return nullptr;
  }

  return c_tinyusd_prim_new(prim_type_name, nullptr);
}

int c_tinyusd_prim_free(CTinyUSDPrim *prim) {
  if (!prim) {
    return 0;
  }

  Prim *p = reinterpret_cast<Prim *>(prim);
  delete p;

  return 1;
}

int c_tinyusd_prim_to_string(const CTinyUSDPrim *prim, c_tinyusd_string_t *str) {
  if (!prim) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  const Prim *p = reinterpret_cast<const Prim *>(prim);

  std::string s = tinyusdz::to_string(*p);

  if (!c_tinyusd_string_replace(str, s.c_str())) {
    return 0;
  }

  return 1;
}

CTinyUSDStage *c_tinyusd_stage_new() {

  auto *buf = new tinyusdz::Stage();
  return reinterpret_cast<CTinyUSDStage*>(buf);
}

int c_tinyusd_stage_to_string(const CTinyUSDStage *stage,
                              c_tinyusd_string_t *str) {
  if (!stage) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  const auto *p = reinterpret_cast<const tinyusdz::Stage *>(stage);
  std::string s = p->ExportToString();

  return c_tinyusd_string_replace(str, s.c_str());
}

int c_tinyusd_stage_free(CTinyUSDStage *stage) {
  if (!stage) {
    return 0;
  }

  tinyusdz::Stage *ptr = reinterpret_cast<tinyusdz::Stage *>(stage);
  delete ptr;

  return 1;
}

int c_tinyusd_stage_traverse(const CTinyUSDStage *_stage,
                             CTinyUSDTraversalFunction callback_fun,
                             c_tinyusd_string_t *_err) {
  if (!_stage) {
    if (_err) {
      c_tinyusd_string_replace(_err, "`stage` argument is null.\n");
    }
    return 0;
  }

  const tinyusdz::Stage *pstage =
      reinterpret_cast<const tinyusdz::Stage *>(_stage);

  DCOUT("visit prims\n");

  std::string err;
  if (!tinyusdz::tydra::VisitPrims(*pstage, CVisitPrimFunction,
                                   reinterpret_cast<void *>(callback_fun),
                                   &err)) {
    if (_err) {
      c_tinyusd_string_replace(_err, err.c_str());
    }
  }

  return 1;
}

CTinyUSDValue *c_tinyusd_value_new_null() {

  auto *pv = new tinyusdz::value::Value(nullptr);

  return reinterpret_cast<CTinyUSDValue *>(pv);
}

int c_tinyusd_value_is_type(const CTinyUSDValue *_value, CTinyUSDValueType value_type) {

  if (!_value) {
    return 0;
  }

  const tinyusdz::value::Value *value = reinterpret_cast<const tinyusdz::value::Value *>(_value);
  const char *ctyname = c_tinyusd_value_type_name(value_type);

  if (value->type_name() == std::string(ctyname)) {
    return 1;
  }

  return 0;
}

int c_tinyusd_value_free(CTinyUSDValue *aval) {
  if (!aval) {
    return 0;
  }

  tinyusdz::value::Value *vp = reinterpret_cast<tinyusdz::value::Value *>(aval);
  delete vp;

  return 1;
}

CTinyUSDValue *c_tinyusd_value_new_token(const c_tinyusd_token_t *tok) {
  if (!tok) {
    return nullptr;
  }

  auto *pv = reinterpret_cast<const tinyusdz::value::token *>(tok);

  // copies.
  tinyusdz::value::Value *vp = new tinyusdz::value::Value(*pv);

  return reinterpret_cast<CTinyUSDValue *>(vp);
}

CTinyUSDValue *c_tinyusd_value_new_string(const c_tinyusd_string_t *str) {
  if (!str) {
    return nullptr;
  }

  auto *pv = reinterpret_cast<const std::string *>(str);

  // copies.
  tinyusdz::value::Value *vp = new tinyusdz::value::Value(*pv);

  return reinterpret_cast<CTinyUSDValue *>(vp);
}

#define ATTRIB_VALUE_NEW_IMPL(__tyname, __cppty, __cty, __tyenum) \
CTinyUSDValue *c_tinyusd_value_new_##__tyname(__cty val) { \
  (void)__tyenum; \
  /* ensure C++ and C types has same size. */ \
  static_assert(sizeof(__cppty) == sizeof(__cty), ""); \
  __cppty cppval; \
  memcpy(&cppval, &val, sizeof(__cppty)); \
  tinyusdz::value::Value *vp = new tinyusdz::value::Value(cppval); \
  return reinterpret_cast<CTinyUSDValue *>(vp); \
}

ATTRIB_VALUE_NEW_IMPL(int, int, int, C_TINYUSD_VALUE_INT)
ATTRIB_VALUE_NEW_IMPL(int2, value::int2, c_tinyusd_int2_t, C_TINYUSD_VALUE_INT2)
ATTRIB_VALUE_NEW_IMPL(int3, value::int3, c_tinyusd_int3_t, C_TINYUSD_VALUE_INT3)
ATTRIB_VALUE_NEW_IMPL(int4, value::int4, c_tinyusd_int4_t, C_TINYUSD_VALUE_INT4)

ATTRIB_VALUE_NEW_IMPL(float, float, float, C_TINYUSD_VALUE_FLOAT)
ATTRIB_VALUE_NEW_IMPL(float2, value::float2, c_tinyusd_float2_t, C_TINYUSD_VALUE_FLOAT2)
ATTRIB_VALUE_NEW_IMPL(float3, value::float3, c_tinyusd_float3_t, C_TINYUSD_VALUE_FLOAT3)
ATTRIB_VALUE_NEW_IMPL(float4, value::float4, c_tinyusd_float4_t, C_TINYUSD_VALUE_FLOAT4)

#undef ATTRIB_VALUE_NEW_IMPL

#define ATTRIB_VALUE_NEW_ARRAY_IMPL(__tyname, __cppty, __cty, __tyenum) \
CTinyUSDValue *c_tinyusd_value_new_array_##__tyname(uint64_t n, const __cty *vals) { \
  (void)__tyenum; \
  /* ensure C++ and C types has same size. */ \
  static_assert(sizeof(__cppty) == sizeof(__cty), ""); \
  std::vector<__cppty> cppvalarray; \
  cppvalarray.resize(size_t(n)); \
  memcpy(cppvalarray.data(), &vals, sizeof(__cppty) * size_t(n)); \
  tinyusdz::value::Value *vp = new tinyusdz::value::Value(std::move(cppvalarray)); \
  return reinterpret_cast<CTinyUSDValue *>(vp); \
}

ATTRIB_VALUE_NEW_ARRAY_IMPL(int, int, int, C_TINYUSD_VALUE_INT)
ATTRIB_VALUE_NEW_ARRAY_IMPL(int2, value::int2, c_tinyusd_int2_t, C_TINYUSD_VALUE_INT2)
ATTRIB_VALUE_NEW_ARRAY_IMPL(int3, value::int3, c_tinyusd_int3_t, C_TINYUSD_VALUE_INT3)
ATTRIB_VALUE_NEW_ARRAY_IMPL(int4, value::int4, c_tinyusd_int4_t, C_TINYUSD_VALUE_INT4)

ATTRIB_VALUE_NEW_ARRAY_IMPL(float, float, float, C_TINYUSD_VALUE_FLOAT)
ATTRIB_VALUE_NEW_ARRAY_IMPL(float2, value::float2, c_tinyusd_float2_t, C_TINYUSD_VALUE_FLOAT2)
ATTRIB_VALUE_NEW_ARRAY_IMPL(float3, value::float3, c_tinyusd_float3_t, C_TINYUSD_VALUE_FLOAT3)
ATTRIB_VALUE_NEW_ARRAY_IMPL(float4, value::float4, c_tinyusd_float4_t, C_TINYUSD_VALUE_FLOAT4)

#undef ATTRIB_VALUE_NEW_ARRAY_IMPL

#define ATTRIB_VALUE_AS_IMPL(__tyname, __cppty, __cty) \
int c_tinyusd_value_as_##__tyname(const CTinyUSDValue *_value, __cty *val) { \
  /* ensure C++ and C types has same size. */ \
  static_assert(sizeof(__cppty) == sizeof(__cty), ""); \
  if (!_value) { return 0; } \
  const tinyusdz::value::Value *vp = reinterpret_cast<const tinyusdz::value::Value *>(_value); \
  if (auto pv = vp->as<__cppty>()) { \
    memcpy(val, pv, sizeof(__cppty)); \
    return 1; \
  } \
  return 0; \
}

ATTRIB_VALUE_AS_IMPL(int, int, int);
ATTRIB_VALUE_AS_IMPL(int2, value::int2, c_tinyusd_int2_t);
ATTRIB_VALUE_AS_IMPL(int3, value::int3, c_tinyusd_int3_t);
ATTRIB_VALUE_AS_IMPL(int4, value::int4, c_tinyusd_int4_t);

ATTRIB_VALUE_AS_IMPL(float, float, float);
ATTRIB_VALUE_AS_IMPL(float2, value::float2, c_tinyusd_float2_t);
ATTRIB_VALUE_AS_IMPL(float3, value::float3, c_tinyusd_float3_t);
ATTRIB_VALUE_AS_IMPL(float4, value::float4, c_tinyusd_float4_t);

int c_tinyusd_value_as_string(const CTinyUSDValue *_value,
                              c_tinyusd_string_t *val) {
  if (!_value) {
    return 0;
  }

  if (!val) {
    return 0;
  }

  const tinyusdz::value::Value *vp =
      reinterpret_cast<const tinyusdz::value::Value *>(_value);
  if (const auto pv = vp->as<std::string>()) {
    return c_tinyusd_string_replace(val, pv->c_str());
  }

  return 0;
}

int c_tinyusd_value_as_token(const CTinyUSDValue *_value,
                             c_tinyusd_string_t *val) {
  if (!_value) {
    return 0;
  }

  if (!val) {
    return 0;
  }

  const tinyusdz::value::Value *vp =
      reinterpret_cast<const tinyusdz::value::Value *>(_value);
  if (const auto pv = vp->as<tinyusdz::value::token>()) {
    return c_tinyusd_string_replace(val, pv->str().c_str());
  }

  return 0;
}

int c_tinyusd_value_array_size(const CTinyUSDValue *_value, uint64_t *n) {
  if (!_value) {
    return 0;
  }

  if (!n) {
    return 0;
  }

  const tinyusdz::value::Value *vp =
      reinterpret_cast<const tinyusdz::value::Value *>(_value);
  (*n) = uint64_t(vp->array_size());
  return 1;
}

int c_tinyusd_value_as_array_int(const CTinyUSDValue *_value, int *vals,
                                 uint64_t n) {
  if (!_value) {
    return 0;
  }

  if (!vals && n > 0) {
    return 0;
  }

  const tinyusdz::value::Value *vp =
      reinterpret_cast<const tinyusdz::value::Value *>(_value);
  if (const auto pv = vp->as<std::vector<int>>()) {
    if (pv->size() > size_t(n)) {
      return 0;
    }

    if (!pv->empty()) {
      memcpy(vals, pv->data(), sizeof(int) * pv->size());
    }

    return 1;
  }

  return 0;
}

int c_tinyusd_value_as_array_float(const CTinyUSDValue *_value, float *vals,
                                   uint64_t n) {
  if (!_value) {
    return 0;
  }

  if (!vals && n > 0) {
    return 0;
  }

  const tinyusdz::value::Value *vp =
      reinterpret_cast<const tinyusdz::value::Value *>(_value);
  if (const auto pv = vp->as<std::vector<float>>()) {
    if (pv->size() > size_t(n)) {
      return 0;
    }

    if (!pv->empty()) {
      memcpy(vals, pv->data(), sizeof(float) * pv->size());
    }

    return 1;
  }

  return 0;
}


int c_tinyusd_value_to_string(const CTinyUSDValue *aval, c_tinyusd_string_t *str) {
  if (!aval) {
    return 0;
  }

  if (!str) {
    return 0;
  }

  const tinyusdz::value::Value *cp = reinterpret_cast<const tinyusdz::value::Value *>(aval);

  std::string s = tinyusdz::value::pprint_value(*cp, /* indent */0, /* closing_brace */false);

  if (!c_tinyusd_string_replace(str, s.c_str())) {
    return 0;
  }

  return 1;
}

int c_tinyusd_prim_get_property_names(const CTinyUSDPrim *prim, c_tinyusd_token_vector_t *prop_names_out) {
  if (!prim) {
    return 0;
  }

  if (!prop_names_out) {
    return 0;
  }

  const Prim *p = reinterpret_cast<const Prim *>(prim);
  std::vector<std::string> ps;
  std::string err;
  std::vector<std::string> rs;
  std::string rel_err;

  bool has_any = false;
  if (tydra::GetPropertyNames(*p, &ps, &err)) {
    has_any = true;
  }

  if (tydra::GetRelationshipNames(*p, &rs, &rel_err)) {
    has_any = true;

    for (const auto &r : rs) {
      if (std::find(ps.begin(), ps.end(), r) == ps.end()) {
        ps.push_back(r);
      }
    }
  }

  auto append_name = [&ps](const std::string &name) {
    if (std::find(ps.begin(), ps.end(), name) == ps.end()) {
      ps.push_back(name);
    }
  };

  auto append_props_map = [&append_name](const auto &typed_prim) {
    for (const auto &kv : typed_prim.props) {
      append_name(kv.first);
    }
  };

  auto append_property_names_tokens = [&append_name](const auto &typed_prim) {
    for (const auto &tok : typed_prim.propertyNames()) {
      append_name(tok.str());
    }
  };

  auto append_names_for_typed_prim = [&](const auto &typed_prim) {
    append_props_map(typed_prim);
    append_property_names_tokens(typed_prim);
  };

  if (p->is<tinyusdz::Model>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::Model>());
    has_any = true;
  } else if (p->is<tinyusdz::Xform>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::Xform>());
    has_any = true;
  } else if (p->is<tinyusdz::Scope>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::Scope>());
    has_any = true;
  } else if (p->is<tinyusdz::GeomMesh>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::GeomMesh>());
    has_any = true;
  } else if (p->is<tinyusdz::GeomSubset>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::GeomSubset>());
    has_any = true;
  } else if (p->is<tinyusdz::GeomCamera>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::GeomCamera>());
    has_any = true;
  } else if (p->is<tinyusdz::Shader>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::Shader>());
    has_any = true;
  } else if (p->is<tinyusdz::Material>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::Material>());
    has_any = true;
  } else if (p->is<tinyusdz::SkelRoot>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::SkelRoot>());
    has_any = true;
  } else if (p->is<tinyusdz::BlendShape>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::BlendShape>());
    has_any = true;
  } else if (p->is<tinyusdz::Skeleton>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::Skeleton>());
    has_any = true;
  } else if (p->is<tinyusdz::SkelAnimation>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::SkelAnimation>());
    has_any = true;
  } else if (p->is<tinyusdz::SphereLight>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::SphereLight>());
    has_any = true;
  } else if (p->is<tinyusdz::CylinderLight>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::CylinderLight>());
    has_any = true;
  } else if (p->is<tinyusdz::RectLight>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::RectLight>());
    has_any = true;
  } else if (p->is<tinyusdz::DiskLight>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::DiskLight>());
    has_any = true;
  } else if (p->is<tinyusdz::DistantLight>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::DistantLight>());
    has_any = true;
  } else if (p->is<tinyusdz::DomeLight>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::DomeLight>());
    has_any = true;
  } else if (p->is<tinyusdz::GeometryLight>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::GeometryLight>());
    has_any = true;
  } else if (p->is<tinyusdz::PortalLight>()) {
    append_names_for_typed_prim(*p->as<tinyusdz::PortalLight>());
    has_any = true;
  }

  if (!has_any) {
    return 0;
  }

  if (!c_tinyusd_token_vector_resize(prop_names_out, ps.size())) {
    return 0;
  }

  for (size_t i = 0; i < ps.size(); i++) {
    const std::string &s = ps[i];

    if (!c_tinyusd_token_vector_replace(prop_names_out, i, s.c_str())) {
      return 0;
    }
  }

  return 1;
}

static_assert(sizeof(c_tinyusd_int2_t) == sizeof(float) * 2, "");
static_assert(sizeof(c_tinyusd_int3_t) == sizeof(float) * 3, "");
static_assert(sizeof(c_tinyusd_int4_t) == sizeof(float) * 4, "");
static_assert(sizeof(c_tinyusd_half2_t) == sizeof(uint16_t) * 2, "");
static_assert(sizeof(c_tinyusd_half3_t) == sizeof(uint16_t) * 3, "");
static_assert(sizeof(c_tinyusd_half4_t) == sizeof(uint16_t) * 4, "");
static_assert(sizeof(c_tinyusd_quath_t) == sizeof(uint16_t) * 4, "");
static_assert(sizeof(c_tinyusd_quatf_t) == sizeof(float) * 4, "");
static_assert(sizeof(c_tinyusd_quatd_t) == sizeof(double) * 4, "");

