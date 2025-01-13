/* Compilation switch flag type definitions for GCC.
   Copyright (C) 1987-2025 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_FLAG_TYPES_H
#define GCC_FLAG_TYPES_H

#if !defined(IN_LIBGCC2) && !defined(IN_TARGET_LIBS) && !defined(IN_RTS)

enum debug_info_type
{
  DINFO_TYPE_NONE,		  /* No debug info.  */
  DINFO_TYPE_DWARF2,		  /* Dwarf v2 debug info.  */
  DINFO_TYPE_VMS,		  /* VMS debug info.  */
  DINFO_TYPE_CTF,		  /* CTF debug info.  */
  DINFO_TYPE_BTF,		  /* BTF debug info.  */
  DINFO_TYPE_CODEVIEW,		  /* CodeView debug info.  */
  DINFO_TYPE_BTF_WITH_CORE,	  /* BTF debug info with CO-RE relocations.  */
  DINFO_TYPE_MAX = DINFO_TYPE_BTF_WITH_CORE /* Marker only.  */
};

#define NO_DEBUG      (0U)
/* Write DWARF2 debug info (using dwarf2out.cc).  */
#define DWARF2_DEBUG  (1U << DINFO_TYPE_DWARF2)
/* Write VMS debug info (using vmsdbgout.cc).  */
#define VMS_DEBUG     (1U << DINFO_TYPE_VMS)
/* Write CTF debug info (using ctfout.cc).  */
#define CTF_DEBUG     (1U << DINFO_TYPE_CTF)
/* Write BTF debug info (using btfout.cc).  */
#define BTF_DEBUG     (1U << DINFO_TYPE_BTF)
/* Write CodeView debug info (using dwarf2codeview.cc).  */
#define CODEVIEW_DEBUG     (1U << DINFO_TYPE_CODEVIEW)
/* Write BTF debug info for BPF CO-RE usecase (using btfout.cc).  */
#define BTF_WITH_CORE_DEBUG     (1U << DINFO_TYPE_BTF_WITH_CORE)

/* Note: Adding new definitions to handle -combination- of debug formats,
   like VMS_AND_DWARF2_DEBUG is not recommended.  This definition remains
   here for historical reasons.  */
/* Write VMS debug info (using vmsdbgout.cc) and DWARF v2 debug info (using
   dwarf2out.cc).  */
#define VMS_AND_DWARF2_DEBUG  ((VMS_DEBUG | DWARF2_DEBUG))

enum debug_info_levels
{
  DINFO_LEVEL_NONE,	/* Write no debugging info.  */
  DINFO_LEVEL_TERSE,	/* Write minimal info to support tracebacks only.  */
  DINFO_LEVEL_NORMAL,	/* Write info for all declarations (and line table).  */
  DINFO_LEVEL_VERBOSE	/* Write normal info plus #define/#undef info.  */
};

/* CTF debug info levels.
   CTF debug info levels are untied with DWARF debug info levels because CTF
   may co-exist with DWARF.  */
enum ctf_debug_info_levels
{
  CTFINFO_LEVEL_NONE = 0,     /* Write no CTF debug info.  */
  CTFINFO_LEVEL_TERSE = 1,    /* Write CTF information to support tracebacks
				 only.  Not Implemented.  */
  CTFINFO_LEVEL_NORMAL = 2    /* Write CTF type information for all entities
				 (functions, data objects, variables etc.)
				 at file-scope or global-scope only.  */
};

/* A major contribution to object and executable size is debug
   information size.  A major contribution to debug information
   size is struct descriptions replicated in several object files.
   The following function determines whether or not debug information
   should be generated for a given struct.  The indirect parameter
   indicates that the struct is being handled indirectly, via
   a pointer.  See opts.cc for the implementation. */

enum debug_info_usage
{
  DINFO_USAGE_DFN,	/* A struct definition. */
  DINFO_USAGE_DIR_USE,	/* A direct use, such as the type of a variable. */
  DINFO_USAGE_IND_USE,	/* An indirect use, such as through a pointer. */
  DINFO_USAGE_NUM_ENUMS	/* The number of enumerators. */
};

/* A major contribution to object and executable size is debug
   information size.  A major contribution to debug information size
   is struct descriptions replicated in several object files. The
   following flags attempt to reduce this information.  The basic
   idea is to not emit struct debugging information in the current
   compilation unit when that information will be generated by
   another compilation unit.

   Debug information for a struct defined in the current source
   file should be generated in the object file.  Likewise the
   debug information for a struct defined in a header should be
   generated in the object file of the corresponding source file.
   Both of these case are handled when the base name of the file of
   the struct definition matches the base name of the source file
   of the current compilation unit.  This matching emits minimal
   struct debugging information.

   The base file name matching rule above will fail to emit debug
   information for structs defined in system headers.  So a second
   category of files includes system headers in addition to files
   with matching bases.

   The remaining types of files are library headers and application
   headers.  We cannot currently distinguish these two types.  */

enum debug_struct_file
{
  DINFO_STRUCT_FILE_NONE,   /* Debug no structs. */
  DINFO_STRUCT_FILE_BASE,   /* Debug structs defined in files with the
                               same base name as the compilation unit. */
  DINFO_STRUCT_FILE_SYS,    /* Also debug structs defined in system
                               header files.  */
  DINFO_STRUCT_FILE_ANY     /* Debug structs defined in all files. */
};

/* Balance between GNAT encodings and standard DWARF to emit.  */

enum dwarf_gnat_encodings
{
  DWARF_GNAT_ENCODINGS_ALL = 0,	    /* Emit all GNAT encodings, then emit as
				       much standard DWARF as possible so it
				       does not conflict with GNAT
				       encodings.  */
  DWARF_GNAT_ENCODINGS_GDB = 1,	    /* Emit as much standard DWARF as possible
				       as long as GDB handles them.  Emit GNAT
				       encodings for the rest.  */
  DWARF_GNAT_ENCODINGS_MINIMAL = 2  /* Emit all the standard DWARF we can.
				       Emit GNAT encodings for the rest.  */
};

/* Enumerate Objective-c instance variable visibility settings. */

enum ivar_visibility
{
  IVAR_VISIBILITY_PRIVATE,
  IVAR_VISIBILITY_PROTECTED,
  IVAR_VISIBILITY_PUBLIC,
  IVAR_VISIBILITY_PACKAGE
};

/* The stack reuse level.  */
enum stack_reuse_level
{
  SR_NONE,
  SR_NAMED_VARS,
  SR_ALL
};

/* Control Flow Redundancy hardening options for noreturn calls.  */
enum hardcfr_noret
{
  HCFRNR_NEVER,
  HCFRNR_NOTHROW,
  HCFRNR_NO_XTHROW,
  HCFRNR_UNSPECIFIED,
  HCFRNR_ALWAYS,
};

/* The live patching level.  */
enum live_patching_level
{
  LIVE_PATCHING_NONE = 0,
  LIVE_PATCHING_INLINE_ONLY_STATIC,
  LIVE_PATCHING_INLINE_CLONE
};

/* The algorithm used for basic block reordering.  */
enum reorder_blocks_algorithm
{
  REORDER_BLOCKS_ALGORITHM_SIMPLE,
  REORDER_BLOCKS_ALGORITHM_STC
};

/* The algorithm used for the integrated register allocator (IRA).  */
enum ira_algorithm
{
  IRA_ALGORITHM_CB,
  IRA_ALGORITHM_PRIORITY
};

/* The regions used for the integrated register allocator (IRA).  */
enum ira_region
{
  IRA_REGION_ONE,
  IRA_REGION_ALL,
  IRA_REGION_MIXED,
};

/* The options for excess precision.  */
enum excess_precision
{
  EXCESS_PRECISION_DEFAULT,
  EXCESS_PRECISION_FAST,
  EXCESS_PRECISION_STANDARD,
  EXCESS_PRECISION_FLOAT16
};

/* The options for which values of FLT_EVAL_METHOD are permissible.  */
enum permitted_flt_eval_methods
{
  PERMITTED_FLT_EVAL_METHODS_DEFAULT,
  PERMITTED_FLT_EVAL_METHODS_TS_18661,
  PERMITTED_FLT_EVAL_METHODS_C11
};

/* Type of stack check.

   Stack checking is designed to detect infinite recursion and stack
   overflows for Ada programs.  Furthermore stack checking tries to ensure
   in that scenario that enough stack space is left to run a signal handler.

   -fstack-check= does not prevent stack-clash style attacks.  For that
   you want -fstack-clash-protection.  */
enum stack_check_type
{
  /* Do not check the stack.  */
  NO_STACK_CHECK = 0,

  /* Check the stack generically, i.e. assume no specific support
     from the target configuration files.  */
  GENERIC_STACK_CHECK,

  /* Check the stack and rely on the target configuration files to
     check the static frame of functions, i.e. use the generic
     mechanism only for dynamic stack allocations.  */
  STATIC_BUILTIN_STACK_CHECK,

  /* Check the stack and entirely rely on the target configuration
     files, i.e. do not use the generic mechanism at all.  */
  FULL_BUILTIN_STACK_CHECK
};

/* Type of callgraph information.  */
enum callgraph_info_type
{
  /* No information.  */
  NO_CALLGRAPH_INFO = 0,

  /* Naked callgraph.  */
  CALLGRAPH_INFO_NAKED = 1,

  /* Callgraph decorated with stack usage information.  */
  CALLGRAPH_INFO_STACK_USAGE = 2,

  /* Callgraph decoration with dynamic allocation information.  */
  CALLGRAPH_INFO_DYNAMIC_ALLOC = 4
};

/* Floating-point contraction mode.  */
enum fp_contract_mode {
  FP_CONTRACT_OFF = 0,
  FP_CONTRACT_ON = 1,
  FP_CONTRACT_FAST = 2
};

/* Scalar storage order kind.  */
enum scalar_storage_order_kind {
  SSO_NATIVE = 0,
  SSO_BIG_ENDIAN,
  SSO_LITTLE_ENDIAN
};

/* Vectorizer cost-model.  Except for DEFAULT, the values are ordered from
   the most conservative to the least conservative.  */
enum vect_cost_model {
  VECT_COST_MODEL_VERY_CHEAP = -3,
  VECT_COST_MODEL_CHEAP = -2,
  VECT_COST_MODEL_DYNAMIC = -1,
  VECT_COST_MODEL_UNLIMITED = 0,
  VECT_COST_MODEL_DEFAULT = 1
};

/* Automatic variable initialization type.  */
enum auto_init_type {
  AUTO_INIT_UNINITIALIZED = 0,
  AUTO_INIT_PATTERN = 1,
  AUTO_INIT_ZERO = 2
};

/* Initialization of padding bits with zeros.  */
enum zero_init_padding_bits_kind {
  ZERO_INIT_PADDING_BITS_STANDARD = 0,
  ZERO_INIT_PADDING_BITS_UNIONS = 1,
  ZERO_INIT_PADDING_BITS_ALL = 2
};

/* Different instrumentation modes.  */
enum sanitize_code {
  /* AddressSanitizer.  */
  SANITIZE_ADDRESS = 1UL << 0,
  SANITIZE_USER_ADDRESS = 1UL << 1,
  SANITIZE_KERNEL_ADDRESS = 1UL << 2,
  /* ThreadSanitizer.  */
  SANITIZE_THREAD = 1UL << 3,
  /* LeakSanitizer.  */
  SANITIZE_LEAK = 1UL << 4,
  /* UndefinedBehaviorSanitizer.  */
  SANITIZE_SHIFT_BASE = 1UL << 5,
  SANITIZE_SHIFT_EXPONENT = 1UL << 6,
  SANITIZE_DIVIDE = 1UL << 7,
  SANITIZE_UNREACHABLE = 1UL << 8,
  SANITIZE_VLA = 1UL << 9,
  SANITIZE_NULL = 1UL << 10,
  SANITIZE_RETURN = 1UL << 11,
  SANITIZE_SI_OVERFLOW = 1UL << 12,
  SANITIZE_BOOL = 1UL << 13,
  SANITIZE_ENUM = 1UL << 14,
  SANITIZE_FLOAT_DIVIDE = 1UL << 15,
  SANITIZE_FLOAT_CAST = 1UL << 16,
  SANITIZE_BOUNDS = 1UL << 17,
  SANITIZE_ALIGNMENT = 1UL << 18,
  SANITIZE_NONNULL_ATTRIBUTE = 1UL << 19,
  SANITIZE_RETURNS_NONNULL_ATTRIBUTE = 1UL << 20,
  SANITIZE_OBJECT_SIZE = 1UL << 21,
  SANITIZE_VPTR = 1UL << 22,
  SANITIZE_BOUNDS_STRICT = 1UL << 23,
  SANITIZE_POINTER_OVERFLOW = 1UL << 24,
  SANITIZE_BUILTIN = 1UL << 25,
  SANITIZE_POINTER_COMPARE = 1UL << 26,
  SANITIZE_POINTER_SUBTRACT = 1UL << 27,
  SANITIZE_HWADDRESS = 1UL << 28,
  SANITIZE_USER_HWADDRESS = 1UL << 29,
  SANITIZE_KERNEL_HWADDRESS = 1UL << 30,
  /* Shadow Call Stack.  */
  SANITIZE_SHADOW_CALL_STACK = 1UL << 31,
  SANITIZE_SHIFT = SANITIZE_SHIFT_BASE | SANITIZE_SHIFT_EXPONENT,
  SANITIZE_UNDEFINED = SANITIZE_SHIFT | SANITIZE_DIVIDE | SANITIZE_UNREACHABLE
		       | SANITIZE_VLA | SANITIZE_NULL | SANITIZE_RETURN
		       | SANITIZE_SI_OVERFLOW | SANITIZE_BOOL | SANITIZE_ENUM
		       | SANITIZE_BOUNDS | SANITIZE_ALIGNMENT
		       | SANITIZE_NONNULL_ATTRIBUTE
		       | SANITIZE_RETURNS_NONNULL_ATTRIBUTE
		       | SANITIZE_OBJECT_SIZE | SANITIZE_VPTR
		       | SANITIZE_POINTER_OVERFLOW | SANITIZE_BUILTIN,
  SANITIZE_UNDEFINED_NONDEFAULT = SANITIZE_FLOAT_DIVIDE | SANITIZE_FLOAT_CAST
				  | SANITIZE_BOUNDS_STRICT
};

/* Different settings for zeroing subset of registers.  */
namespace zero_regs_flags {
  const unsigned int UNSET = 0;
  const unsigned int SKIP = 1UL << 0;
  const unsigned int ONLY_USED = 1UL << 1;
  const unsigned int ONLY_GPR = 1UL << 2;
  const unsigned int ONLY_ARG = 1UL << 3;
  const unsigned int ENABLED = 1UL << 4;
  const unsigned int LEAFY_MODE = 1UL << 5;
  const unsigned int USED_GPR_ARG = ENABLED | ONLY_USED | ONLY_GPR | ONLY_ARG;
  const unsigned int USED_GPR = ENABLED | ONLY_USED | ONLY_GPR;
  const unsigned int USED_ARG = ENABLED | ONLY_USED | ONLY_ARG;
  const unsigned int USED = ENABLED | ONLY_USED;
  const unsigned int ALL_GPR_ARG = ENABLED | ONLY_GPR | ONLY_ARG;
  const unsigned int ALL_GPR = ENABLED | ONLY_GPR;
  const unsigned int ALL_ARG = ENABLED | ONLY_ARG;
  const unsigned int ALL = ENABLED;
  const unsigned int LEAFY_GPR_ARG = ENABLED | LEAFY_MODE | ONLY_GPR | ONLY_ARG;
  const unsigned int LEAFY_GPR = ENABLED | LEAFY_MODE | ONLY_GPR;
  const unsigned int LEAFY_ARG = ENABLED | LEAFY_MODE | ONLY_ARG;
  const unsigned int LEAFY = ENABLED | LEAFY_MODE;
}

/* Settings of flag_incremental_link.  */
enum incremental_link {
  INCREMENTAL_LINK_NONE,
  /* Do incremental linking and produce binary.  */
  INCREMENTAL_LINK_NOLTO,
  /* Do incremental linking and produce IL.  */
  INCREMENTAL_LINK_LTO
};

/* Different trace modes.  */
enum sanitize_coverage_code {
  /* Trace PC.  */
  SANITIZE_COV_TRACE_PC = 1 << 0,
  /* Trace Comparison.  */
  SANITIZE_COV_TRACE_CMP = 1 << 1
};

/* flag_vtable_verify initialization levels. */
enum vtv_priority {
  VTV_NO_PRIORITY       = 0,  /* i.E. Do NOT do vtable verification. */
  VTV_STANDARD_PRIORITY = 1,
  VTV_PREINIT_PRIORITY  = 2
};

/* flag_lto_partition initialization values.  */
enum lto_partition_model {
  LTO_PARTITION_NONE = 0,
  LTO_PARTITION_ONE = 1,
  LTO_PARTITION_BALANCED = 2,
  LTO_PARTITION_1TO1 = 3,
  LTO_PARTITION_MAX = 4,
  LTO_PARTITION_CACHE = 5
};

/* flag_lto_linker_output initialization values.  */
enum lto_linker_output {
  LTO_LINKER_OUTPUT_UNKNOWN,
  LTO_LINKER_OUTPUT_REL,
  LTO_LINKER_OUTPUT_NOLTOREL,
  LTO_LINKER_OUTPUT_DYN,
  LTO_LINKER_OUTPUT_PIE,
  LTO_LINKER_OUTPUT_EXEC
};

/* gfortran -finit-real= values.  */

enum gfc_init_local_real
{
  GFC_INIT_REAL_OFF = 0,
  GFC_INIT_REAL_ZERO,
  GFC_INIT_REAL_NAN,
  GFC_INIT_REAL_SNAN,
  GFC_INIT_REAL_INF,
  GFC_INIT_REAL_NEG_INF
};

/* gfortran -fcoarray= values.  */

enum gfc_fcoarray
{
  GFC_FCOARRAY_NONE = 0,
  GFC_FCOARRAY_SINGLE,
  GFC_FCOARRAY_LIB
};


/* gfortran -fconvert= values; used for unformatted I/O.
   Keep in sync with GFC_CONVERT_* in gcc/fortran/libgfortran.h.   */
enum gfc_convert
{
  GFC_FLAG_CONVERT_NATIVE = 0,
  GFC_FLAG_CONVERT_SWAP,
  GFC_FLAG_CONVERT_BIG,
  GFC_FLAG_CONVERT_LITTLE,
  GFC_FLAG_CONVERT_R16_IEEE = 4,
  GFC_FLAG_CONVERT_R16_IEEE_SWAP,
  GFC_FLAG_CONVERT_R16_IEEE_BIG,
  GFC_FLAG_CONVERT_R16_IEEE_LITTLE,
  GFC_FLAG_CONVERT_R16_IBM = 8,
  GFC_FLAG_CONVERT_R16_IBM_SWAP,
  GFC_FLAG_CONVERT_R16_IBM_BIG,
  GFC_FLAG_CONVERT_R16_IBM_LITTLE,
};


/* gfortran -finline-intrinsics= values;
   We use two identical bits for each value, and initialize with alternated
   bits, so that we can check whether a value has been set by checking whether
   the two bits have identical value.  */

#define GFC_INL_INTR_VAL(idx) (3 << (2 * idx))
#define GFC_INL_INTR_UNSET_VAL(val) (0x55555555 & (val))

enum gfc_inlineable_intrinsics
{
  GFC_FLAG_INLINE_INTRINSIC_NONE = 0,
  GFC_FLAG_INLINE_INTRINSIC_MAXLOC = GFC_INL_INTR_VAL (0),
  GFC_FLAG_INLINE_INTRINSIC_MINLOC = GFC_INL_INTR_VAL (1),
  GFC_FLAG_INLINE_INTRINSIC_ALL = GFC_FLAG_INLINE_INTRINSIC_MAXLOC
				  | GFC_FLAG_INLINE_INTRINSIC_MINLOC,

  GFC_FLAG_INLINE_INTRINSIC_NONE_UNSET
		  = GFC_INL_INTR_UNSET_VAL (GFC_FLAG_INLINE_INTRINSIC_NONE),
  GFC_FLAG_INLINE_INTRINSIC_MAXLOC_UNSET
		  = GFC_INL_INTR_UNSET_VAL (GFC_FLAG_INLINE_INTRINSIC_MAXLOC),
  GFC_FLAG_INLINE_INTRINSIC_MINLOC_UNSET
		  = GFC_INL_INTR_UNSET_VAL (GFC_FLAG_INLINE_INTRINSIC_MINLOC),
  GFC_FLAG_INLINE_INTRINSIC_ALL_UNSET
		  = GFC_INL_INTR_UNSET_VAL (GFC_FLAG_INLINE_INTRINSIC_ALL)
};

#undef GFC_INL_INTR_UNSET_VAL
#undef GFC_INL_INTR_VAL


/* Inline String Operations functions.  */
enum ilsop_fn
{
  ILSOP_NONE = 0,
  ILSOP_MEMSET = 1 << 0,
  ILSOP_MEMCPY = 1 << 1,
  ILSOP_MEMMOVE = 1 << 2,
  ILSOP_MEMCMP = 1 << 3,
  ILSOP_ALL = -1
};

/* Control-Flow Protection values.  */
enum cf_protection_level
{
  CF_NONE = 0,
  CF_BRANCH = 1 << 0,
  CF_RETURN = 1 << 1,
  CF_FULL = CF_BRANCH | CF_RETURN,
  CF_SET = 1 << 2,
  CF_CHECK = 1 << 3
};

/* Parloops schedule type.  */
enum parloops_schedule_type
{
  PARLOOPS_SCHEDULE_STATIC = 0,
  PARLOOPS_SCHEDULE_DYNAMIC,
  PARLOOPS_SCHEDULE_GUIDED,
  PARLOOPS_SCHEDULE_AUTO,
  PARLOOPS_SCHEDULE_RUNTIME
};

/* Ranger debug mode.  */
enum ranger_debug
{
  RANGER_DEBUG_NONE = 0,
  RANGER_DEBUG_TRACE = 1,
  RANGER_DEBUG_CACHE = 2,
  RANGER_DEBUG_GORI = 4,
  RANGER_DEBUG_TRACE_GORI = (RANGER_DEBUG_TRACE | RANGER_DEBUG_GORI),
  RANGER_DEBUG_TRACE_CACHE = (RANGER_DEBUG_TRACE | RANGER_DEBUG_CACHE),
  RANGER_DEBUG_ALL = (RANGER_DEBUG_GORI | RANGER_DEBUG_CACHE
		      | RANGER_DEBUG_TRACE)
};

/* Jump threader verbose dumps.  */
enum threader_debug
{
  THREADER_DEBUG_NONE = 0,
  THREADER_DEBUG_ALL = 1
};

/* Modes of OpenACC 'kernels' constructs handling.  */
enum openacc_kernels
{
  OPENACC_KERNELS_DECOMPOSE,
  OPENACC_KERNELS_PARLOOPS
};

/* Modes of OpenACC privatization diagnostics.  */
enum openacc_privatization
{
  OPENACC_PRIVATIZATION_QUIET,
  OPENACC_PRIVATIZATION_NOISY
};

/* Targets for -fopenmp-target-simd-clone.  */
enum omp_target_simd_clone_device_kind
{
  OMP_TARGET_SIMD_CLONE_NONE = 0,
  OMP_TARGET_SIMD_CLONE_HOST = 1,
  OMP_TARGET_SIMD_CLONE_NOHOST = 2,
  OMP_TARGET_SIMD_CLONE_ANY = 3
};

#endif

#endif /* ! GCC_FLAG_TYPES_H */
