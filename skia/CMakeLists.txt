#
# 新しいCmakeを使うように
# OpenMPに対応したGCCを使うように
#

cmake_minimum_required(VERSION 3.26.4)
project(reskia)
#set(CMAKE_C_COMPILER "gcc")

include_directories(${PROJECT_SOURCE_DIR}/)
link_directories(${PROJECT_SOURCE_DIR}/lib)
#include(${PROJECT_SOURCE_DIR}/src)

set(CMAKE_CXX_STANDARD 17)

#find_package(OpenMP REQUIRED)
#
#if(NOT OpenMP_C_FOUND)
#    message(FATAL_ERROR "OpenMP not found")
#endif()

# CUDAアーキテクチャをターゲットにする場合のフラグを設定
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp-targets=nvptx64-nvidia-cuda")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp")
#add_compile_options(-fopenmp)

add_library(reskia SHARED
        binding/reskia.cpp
        src/core/SkColor.cpp
        src/core/SkBitmap.cpp
        src/core/SkColorSpaceXformSteps.cpp
        src/core/SkConvertPixels.cpp
        src/core/SkRasterPipeline.cpp
        src/base/SkHalf.cpp
        src/core/SkCpu.cpp
        src/core/SkOpts.cpp
        src/base/SkArenaAlloc.cpp
        src/sksl/tracing/SkSLTraceHook.cpp
        src/sksl/SkSLPosition.cpp
        src/sksl/ir/SkSLType.cpp
        src/base/SkMathPriv.cpp
        src/base/SkSafeMath.cpp
        src/core/SkChecksum.cpp
        src/sksl/ir/SkSLConstructorArrayCast.cpp
        src/sksl/ir/SkSLConstructorArray.cpp
        src/sksl/ir/SkSLConstructor.cpp
        src/sksl/ir/SkSLConstructorCompound.cpp
        src/sksl/ir/SkSLConstructorCompoundCast.cpp
        src/sksl/ir/SkSLConstructorDiagonalMatrix.cpp
        src/sksl/ir/SkSLConstructorMatrixResize.cpp
        src/sksl/ir/SkSLConstructorScalarCast.cpp
        src/sksl/ir/SkSLConstructorSplat.cpp
        src/sksl/ir/SkSLConstructorStruct.cpp
        src/sksl/ir/SkSLExpression.cpp
        src/sksl/ir/SkSLLayout.cpp
        src/sksl/ir/SkSLLiteral.cpp
        src/sksl/ir/SkSLSymbolTable.cpp
        src/sksl/ir/SkSLFunctionDeclaration.cpp
        src/sksl/ir/SkSLInterfaceBlock.cpp
        src/sksl/ir/SkSLVarDeclarations.cpp
        src/sksl/SkSLAnalysis.cpp
        src/sksl/ir/SkSLBinaryExpression.cpp
        src/sksl/ir/SkSLBlock.cpp
        src/sksl/ir/SkSLChildCall.cpp
        src/sksl/ir/SkSLDoStatement.cpp
        src/sksl/ir/SkSLExpressionStatement.cpp
        src/sksl/ir/SkSLFieldAccess.cpp
        src/sksl/ir/SkSLForStatement.cpp
        src/sksl/ir/SkSLFunctionCall.cpp
        src/sksl/ir/SkSLFunctionDefinition.cpp
        src/sksl/ir/SkSLIfStatement.cpp
        src/sksl/ir/SkSLIndexExpression.cpp
        src/sksl/ir/SkSLPostfixExpression.cpp
        src/sksl/ir/SkSLPrefixExpression.cpp
        src/sksl/ir/SkSLProgram.cpp
        src/sksl/ir/SkSLSetting.cpp
        src/sksl/ir/SkSLSwitchCase.cpp
        src/sksl/ir/SkSLSwitchStatement.cpp
        src/sksl/ir/SkSLSwizzle.cpp
        src/sksl/ir/SkSLTernaryExpression.cpp
        src/sksl/ir/SkSLTypeReference.cpp
        src/sksl/ir/SkSLVariable.cpp
        src/sksl/ir/SkSLVariableReference.cpp
        src/sksl/SkSLBuiltinTypes.cpp
        src/sksl/SkSLCompiler.cpp
        src/sksl/SkSLConstantFolder.cpp
        src/sksl/SkSLContext.cpp
        src/sksl/SkSLErrorReporter.cpp
        src/sksl/SkSLInliner.cpp
        src/sksl/SkSLIntrinsicList.cpp
        src/sksl/SkSLMangler.cpp
        src/sksl/SkSLModuleLoader.cpp
        src/sksl/SkSLOperator.cpp
        src/sksl/SkSLOutputStream.cpp
        src/sksl/SkSLParser.cpp
        src/core/SkMatrixInvert.cpp
        src/sksl/ir/SkSLDiscardStatement.cpp
        src/sksl/ir/SkSLExtension.cpp
        src/sksl/ir/SkSLModifiersDeclaration.cpp
        src/sksl/ir/SkSLStructDefinition.cpp
        src/sksl/SkSLLexer.cpp
        src/sksl/SkSLPool.cpp
        src/sksl/SkSLString.cpp
        src/sksl/SkSLThreadContext.cpp
        src/sksl/SkSLUtil.cpp
        src/sksl/analysis/SkSLProgramUsage.cpp
        src/core/SkSLTypeShared.cpp
        src/core/SkData.cpp
        src/core/SkStream.cpp
        src/core/SkPixmap.cpp
        src/core/SkMatrix.cpp
        src/core/SkRect.cpp
        src/core/SkStringUtils.cpp
        src/core/SkReadPixelsRec.cpp
        src/base/SkUTF.cpp
        src/core/SkMask.cpp
        src/core/SkColorSpace.cpp
        src/core/SkCachedData.cpp
        src/core/SkImageInfo.cpp
        src/core/SkPixelRef.cpp
        src/core/SkBitmapCache.cpp
        src/core/SkString.cpp
        src/core/SkPath.cpp
        src/core/SkEdgeClipper.cpp
)

target_link_libraries(reskia
        $<$<PLATFORM_ID:Darwin>: skcms>
        $<$<PLATFORM_ID:Linux>:skcms>
        $<$<PLATFORM_ID:Windows>: skcms>
)

# set_target_properties(raia_primitive PROPERTIES PREFIX "")