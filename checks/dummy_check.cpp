#include "dummy_check.hpp"

namespace clang::tidy {

DummyCheck::DummyCheck(StringRef name, ClangTidyContext* context) : ClangTidyCheck(name, context) {
}

void DummyCheck::registerMatchers(ast_matchers::MatchFinder* finder) {
    // finder->addMatcher(ast_matchers::declRefExpr(ast_matchers::isConstQualified()).bind("x"), this);
    using namespace ast_matchers;
    finder->addMatcher(
        declRefExpr(hasDeclaration(namedDecl(matchesName("nlanes")))).bind("x"),
        this);
}

void DummyCheck::check(const ast_matchers::MatchFinder::MatchResult& result) {
    const auto *MatchedDecl = result.Nodes.getNodeAs<DeclRefExpr>("x");
    if (MatchedDecl && MatchedDecl->getNameInfo().getName().getAsString() == "nlanes")
    {
        diag(MatchedDecl->getLocation(), "Found lanes number %0 (%1)")
            << MatchedDecl->getNameInfo().getName();
        // MatchedDecl->dump(llvm::outs());
    }
    // MatchedDecl->getQualifier()->dump();
        // << MatchedDecl->getNameInfo()
        // << MatchedDecl->getFoundDecl();
}

} // clang::tidy::

// /work/opencv/modules/core/include/opencv2/core/hal/intrin.hpp:731:36: note: "root" binds here
//         enum { nlanes = T::nlanes, max_nlanes = T::nlanes };
//                                    ^~~~~~~~~~~~~~~~~~~~~~
// Binding for "root":
// max_nlanes = v_float64x2::nlanes
// Binding for "root":
// EnumConstantDecl 0x679d240 </work/opencv/modules/core/include/opencv2/core/hal/intrin.hpp:731:36, col:52> col:36 max_nlanes 'cv::hal_baseline::simd128_cpp::VTraits<cv::hal_baseline::v_float64x2>::(unnamed enum at /work/opencv/modules/core/include/opencv2/core/hal/intrin.hpp:731:9)'
// `-ImplicitCastExpr 0x679d2a8 <col:49, col:52> 'unsigned int' <IntegralCast>
//   `-ConstantExpr 0x679d220 <col:49, col:52> 'cv::hal_baseline::v_float64x2::(unnamed enum at /work/opencv/modules/core/include/opencv2/core/hal/intrin_sse.hpp:308:5)'
//     |-value: Int 2
//     `-DeclRefExpr 0x679d1f0 <col:49, col:52> 'cv::hal_baseline::v_float64x2::(unnamed enum at /work/opencv/modules/core/include/opencv2/core/hal/intrin_sse.hpp:308:5)' EnumConstant 0x6507e10 'nlanes' 'cv::hal_baseline::v_float64x2::(unnamed enum at /work/opencv/modules/core/include/opencv2/core/hal/intrin_sse.hpp:308:5)'

