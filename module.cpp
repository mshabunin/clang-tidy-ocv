#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

#include "checks/dummy_check.hpp"

namespace clang::tidy {

class OCVModule : public ClangTidyModule
{
public:
    void addCheckFactories(ClangTidyCheckFactories& checkFactories) override {
        checkFactories.registerCheck<DummyCheck>("dummy-check");
  }
};

static const char * desc = "Checks and refactor for OpenCV library and its' users";
static ClangTidyModuleRegistry::Add<OCVModule> X("ocv_tidy", desc);

} // clang::tidy::
