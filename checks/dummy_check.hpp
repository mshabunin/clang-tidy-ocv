#ifndef DUMMY_CHECK_HPP
#define DUMMY_CHECK_HPP

#include <clang-tidy/ClangTidyCheck.h>

namespace clang::tidy {

class DummyCheck : public ClangTidyCheck
{
public:
  DummyCheck(StringRef name, ClangTidyContext* context);
  void registerMatchers(ast_matchers::MatchFinder* finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult& result) override;
};

} // clang::tidy::


#endif // DUMMY_CHECK_HPP
