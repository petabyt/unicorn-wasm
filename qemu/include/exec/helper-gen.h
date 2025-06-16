/* Helper file for declaring TCG helper functions.
   This one expands generation functions for tcg opcodes.  */

#ifndef HELPER_GEN_H
#define HELPER_GEN_H 1

#include <exec/helper-head.h>

// Compile-time dispatch
#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define PROBE(x) x, 1
#define CHECK(...) CHECK_N(__VA_ARGS__, 0)
#define CHECK_N(x, n, ...) n

// Void type detection
#define VOID_TYPE_void ()
#define VOID_TYPE_noreturn ()
#define VOID_PROBE(type)            VOID_PROBE_PROXY(VOID_TYPE_##type)
#define VOID_PROBE_PROXY(...)       VOID_PROBE_PRIMITIVE(__VA_ARGS__)
#define VOID_PROBE_PRIMITIVE(x)     VOID_PROBE_COMBINE_ x
#define VOID_PROBE_COMBINE_(...)    PROBE(~)
#define IS_VOID(type)               CHECK(VOID_PROBE(type))

// Global helper detection
#define GLOB_NAME_uc_tracecode ()
#define GLOB_NAME_div_i32 ()
#define GLOB_NAME_rem_i32 ()
#define GLOB_NAME_divu_i32 ()
#define GLOB_NAME_remu_i32 ()
#define GLOB_NAME_div_i64 ()
#define GLOB_NAME_rem_i64 ()
#define GLOB_NAME_divu_i64 ()
#define GLOB_NAME_remu_i64 ()
#define GLOB_NAME_shl_i64 ()
#define GLOB_NAME_shr_i64 ()
#define GLOB_NAME_sar_i64 ()
#define GLOB_NAME_mulsh_i64 ()
#define GLOB_NAME_muluh_i64 ()
#define GLOB_PROBE(name)            GLOB_PROBE_PROXY(GLOB_NAME_##name)
#define GLOB_PROBE_PROXY(...)       GLOB_PROBE_PRIMITIVE(__VA_ARGS__)
#define GLOB_PROBE_PRIMITIVE(x)     GLOB_PROBE_COMBINE_ x
#define GLOB_PROBE_COMBINE_(...)    PROBE(~)
#define IS_GLOB(name)               CHECK(GLOB_PROBE(name))

// Arguments
#define A1 (a1 | ((uint64_t)a2  << 32))
#define A2 (a3 | ((uint64_t)a4  << 32))
#define A3 (a5 | ((uint64_t)a6  << 32))
#define A4 (a7 | ((uint64_t)a8  << 32))
#define A5 (a9 | ((uint64_t)a10 << 32))
#define GEN_ADAPTER_ARGS \
  uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5, \
  uint32_t a6, uint32_t a7, uint32_t a8, uint32_t a9, uint32_t a10

// Adapter definition
#define GEN_ADAPTER_0_VOID(name) \
    HELPER(name)(); return 0;
#define GEN_ADAPTER_0_NONVOID(name) \
    return HELPER(name)();
#define GEN_ADAPTER_0_DEFINE(name, ret) \
uint64_t glue(adapter_helper_, name)(GEN_ADAPTER_ARGS) { \
    IIF(IS_VOID(ret)) (GEN_ADAPTER_0_VOID(name), GEN_ADAPTER_0_NONVOID(name)) \
}

#define GEN_ADAPTER_1_VOID(name, t1) \
    HELPER(name)((dh_ctype(t1))A1); return 0;
#define GEN_ADAPTER_1_NONVOID(name, t1) \
    return HELPER(name)((dh_ctype(t1))A1);
#define GEN_ADAPTER_1_DEFINE(name, ret, t1) \
uint64_t glue(adapter_helper_, name)(GEN_ADAPTER_ARGS) { \
    IIF(IS_VOID(ret)) (GEN_ADAPTER_1_VOID(name, t1), GEN_ADAPTER_1_NONVOID(name, t1)) \
}

#define GEN_ADAPTER_2_VOID(name, t1, t2) \
    HELPER(name)((dh_ctype(t1))A1, (dh_ctype(t2))A2); return 0;
#define GEN_ADAPTER_2_NONVOID(name, t1, t2) \
    return HELPER(name)((dh_ctype(t1))A1, (dh_ctype(t2))A2);
#define GEN_ADAPTER_2_DEFINE(name, ret, t1, t2) \
uint64_t glue(adapter_helper_, name)(GEN_ADAPTER_ARGS) { \
    IIF(IS_VOID(ret)) (GEN_ADAPTER_2_VOID(name, t1, t2), GEN_ADAPTER_2_NONVOID(name, t1, t2)) \
}

#define GEN_ADAPTER_3_VOID(name, t1, t2, t3) \
    HELPER(name)((dh_ctype(t1))A1, (dh_ctype(t2))A2, (dh_ctype(t3))A3); return 0;
#define GEN_ADAPTER_3_NONVOID(name, t1, t2, t3) \
    return HELPER(name)((dh_ctype(t1))A1, (dh_ctype(t2))A2, (dh_ctype(t3))A3);
#define GEN_ADAPTER_3_DEFINE(name, ret, t1, t2, t3) \
uint64_t glue(adapter_helper_, name)(GEN_ADAPTER_ARGS) { \
    IIF(IS_VOID(ret)) (GEN_ADAPTER_3_VOID(name, t1, t2, t3), GEN_ADAPTER_3_NONVOID(name, t1, t2, t3)) \
}

#define GEN_ADAPTER_4_VOID(name, t1, t2, t3, t4) \
    HELPER(name)((dh_ctype(t1))A1, (dh_ctype(t2))A2, (dh_ctype(t3))A3, (dh_ctype(t4))A4); return 0;
#define GEN_ADAPTER_4_NONVOID(name, t1, t2, t3, t4) \
    return HELPER(name)((dh_ctype(t1))A1, (dh_ctype(t2))A2, (dh_ctype(t3))A3, (dh_ctype(t4))A4);
#define GEN_ADAPTER_4_DEFINE(name, ret, t1, t2, t3, t4) \
uint64_t glue(adapter_helper_, name)(GEN_ADAPTER_ARGS) { \
    IIF(IS_VOID(ret)) (GEN_ADAPTER_4_VOID(name, t1, t2, t3, t4), GEN_ADAPTER_4_NONVOID(name, t1, t2, t3, t4)) \
}

#define GEN_ADAPTER_5_VOID(name, t1, t2, t3, t4, t5) \
    HELPER(name)((dh_ctype(t1))A1, (dh_ctype(t2))A2, (dh_ctype(t3))A3, (dh_ctype(t4))A4, (dh_ctype(t5))A5); return 0;
#define GEN_ADAPTER_5_NONVOID(name, t1, t2, t3, t4, t5) \
    return HELPER(name)((dh_ctype(t1))A1, (dh_ctype(t2))A2, (dh_ctype(t3))A3, (dh_ctype(t4))A4, (dh_ctype(t5))A5);
#define GEN_ADAPTER_5_DEFINE(name, ret, t1, t2, t3, t4, t5) \
uint64_t glue(adapter_helper_, name)(GEN_ADAPTER_ARGS) { \
    IIF(IS_VOID(ret)) (GEN_ADAPTER_5_VOID(name, t1, t2, t3, t4, t5), GEN_ADAPTER_5_NONVOID(name, t1, t2, t3, t4, t5)) \
}

#define GEN_ADAPTER_BLANK
#ifdef GEN_ADAPTER_DEFINE
#define GEN_ADAPTER_0(name, ret) \
    IIF(IS_GLOB(name)) (GEN_ADAPTER_BLANK, GEN_ADAPTER_0_DEFINE(name, ret))
#define GEN_ADAPTER_1(name, ret, t1) \
    IIF(IS_GLOB(name)) (GEN_ADAPTER_BLANK, GEN_ADAPTER_1_DEFINE(name, ret, t1))
#define GEN_ADAPTER_2(name, ret, t1, t2) \
    IIF(IS_GLOB(name)) (GEN_ADAPTER_BLANK, GEN_ADAPTER_2_DEFINE(name, ret, t1, t2))
#define GEN_ADAPTER_3(name, ret, t1, t2, t3) \
    IIF(IS_GLOB(name)) (GEN_ADAPTER_BLANK, GEN_ADAPTER_3_DEFINE(name, ret, t1, t2, t3))
#define GEN_ADAPTER_4(name, ret, t1, t2, t3, t4) \
    IIF(IS_GLOB(name)) (GEN_ADAPTER_BLANK, GEN_ADAPTER_4_DEFINE(name, ret, t1, t2, t3, t4))
#define GEN_ADAPTER_5(name, ret, t1, t2, t3, t4, t5) \
    IIF(IS_GLOB(name)) (GEN_ADAPTER_BLANK, GEN_ADAPTER_5_DEFINE(name, ret, t1, t2, t3, t4, t5))
#else
#define GEN_ADAPTER_0(name, ret) GEN_ADAPTER_BLANK
#define GEN_ADAPTER_1(name, ret, t1) GEN_ADAPTER_BLANK
#define GEN_ADAPTER_2(name, ret, t1, t2) GEN_ADAPTER_BLANK
#define GEN_ADAPTER_3(name, ret, t1, t2, t3) GEN_ADAPTER_BLANK
#define GEN_ADAPTER_4(name, ret, t1, t2, t3, t4) GEN_ADAPTER_BLANK
#define GEN_ADAPTER_5(name, ret, t1, t2, t3, t4, t5) GEN_ADAPTER_BLANK
#endif



         #define DEF_HELPER_FLAGS_0(name, flags, ret)                            \
         GEN_ADAPTER_0(name, ret) \
static inline void glue(gen_helper_, name)(TCGContext *tcg_ctx, dh_retvar_decl0(ret))        \
{                                                                       \
  tcg_gen_callN(tcg_ctx, glue(adapter_helper_, name), dh_retvar(ret), 0, NULL);       \
}


         #define DEF_HELPER_FLAGS_1(name, flags, ret, t1)                        \
         GEN_ADAPTER_1(name, ret, t1) \
static inline void glue(gen_helper_, name)(TCGContext *tcg_ctx, dh_retvar_decl(ret)          \
    dh_arg_decl(t1, 1))                            \
{                                                                       \
  TCGArg args[1] = { dh_arg(t1, 1) };                                   \
  tcg_gen_callN(tcg_ctx, glue(adapter_helper_, name), dh_retvar(ret), 1, args);       \
}


         #define DEF_HELPER_FLAGS_2(name, flags, ret, t1, t2)                    \
         GEN_ADAPTER_2(name, ret, t1, t2) \
static inline void glue(gen_helper_, name)(TCGContext *tcg_ctx, dh_retvar_decl(ret)          \
    dh_arg_decl(t1, 1), dh_arg_decl(t2, 2))                             \
{                                                                       \
  TCGArg args[2] = { dh_arg(t1, 1), dh_arg(t2, 2) };                    \
  tcg_gen_callN(tcg_ctx, glue(adapter_helper_, name), dh_retvar(ret), 2, args);       \
}


         #define DEF_HELPER_FLAGS_3(name, flags, ret, t1, t2, t3)                \
         GEN_ADAPTER_3(name, ret, t1, t2, t3) \
static inline void glue(gen_helper_, name)(TCGContext *tcg_ctx, dh_retvar_decl(ret)          \
    dh_arg_decl(t1, 1), dh_arg_decl(t2, 2), dh_arg_decl(t3, 3))         \
{                                                                       \
  TCGArg args[3] = { dh_arg(t1, 1), dh_arg(t2, 2), dh_arg(t3, 3) };     \
  tcg_gen_callN(tcg_ctx, glue(adapter_helper_, name), dh_retvar(ret), 3, args);       \
}


         #define DEF_HELPER_FLAGS_4(name, flags, ret, t1, t2, t3, t4)            \
         GEN_ADAPTER_4(name, ret, t1, t2, t3, t4) \
static inline void glue(gen_helper_, name)(TCGContext *tcg_ctx, dh_retvar_decl(ret)          \
    dh_arg_decl(t1, 1), dh_arg_decl(t2, 2),                             \
    dh_arg_decl(t3, 3), dh_arg_decl(t4, 4))                             \
{                                                                       \
  TCGArg args[4] = { dh_arg(t1, 1), dh_arg(t2, 2),                      \
                     dh_arg(t3, 3), dh_arg(t4, 4) };                    \
  tcg_gen_callN(tcg_ctx, glue(adapter_helper_, name), dh_retvar(ret), 4, args);       \
}


         #define DEF_HELPER_FLAGS_5(name, flags, ret, t1, t2, t3, t4, t5)        \
         GEN_ADAPTER_5(name, ret, t1, t2, t3, t4, t5) \
static inline void glue(gen_helper_, name)(TCGContext *tcg_ctx, dh_retvar_decl(ret)          \
    dh_arg_decl(t1, 1),  dh_arg_decl(t2, 2), dh_arg_decl(t3, 3),        \
    dh_arg_decl(t4, 4), dh_arg_decl(t5, 5))                             \
{                                                                       \
  TCGArg args[5] = { dh_arg(t1, 1), dh_arg(t2, 2), dh_arg(t3, 3),       \
                     dh_arg(t4, 4), dh_arg(t5, 5) };                    \
  tcg_gen_callN(tcg_ctx, glue(adapter_helper_, name), dh_retvar(ret), 5, args);       \
}

#include "helper.h"
#include "tcg-runtime.h"

#undef DEF_HELPER_FLAGS_0
#undef DEF_HELPER_FLAGS_1
#undef DEF_HELPER_FLAGS_2
#undef DEF_HELPER_FLAGS_3
#undef DEF_HELPER_FLAGS_4
#undef DEF_HELPER_FLAGS_5
#undef GEN_HELPER

#endif /* HELPER_GEN_H */
