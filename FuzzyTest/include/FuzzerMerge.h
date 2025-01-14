// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef LLVM_FUZZER_MERGE_H
#define LLVM_FUZZER_MERGE_H

#include "FuzzerDefs.h"

#include <istream>
#include <ostream>
#include <set>
#include <vector>

namespace fuzzer {

struct MergeFileInfo {
  std::string Name;
  size_t Size = 0;
  Vector<uint32_t> Features, Cov;
};

struct Merger {
  Vector<MergeFileInfo> Files;
  size_t NumFilesInFirstCorpus = 0;
  size_t FirstNotProcessedFile = 0;
  std::string LastFailure;

  bool Parse(std::istream &IS, bool ParseCoverage);
  bool Parse(const std::string &Str, bool ParseCoverage);
  void ParseOrExit(std::istream &IS, bool ParseCoverage);
  size_t Merge(const Set<uint32_t> &InitialFeatures, Set<uint32_t> *NewFeatures,
               const Set<uint32_t> &InitialCov, Set<uint32_t> *NewCov,
               Vector<std::string> *NewFiles);
  size_t ApproximateMemoryConsumption() const;
  Set<uint32_t> AllFeatures() const;
};

void CrashResistantMerge(const Vector<std::string> &Args,
                         const Vector<SizedFile> &OldCorpus,
                         const Vector<SizedFile> &NewCorpus,
                         Vector<std::string> *NewFiles,
                         const Set<uint32_t> &InitialFeatures,
                         Set<uint32_t> *NewFeatures,
                         const Set<uint32_t> &InitialCov,
                         Set<uint32_t> *NewCov,
                         const std::string &CFPath,
                         bool Verbose);

}  // namespace fuzzer

#endif  // LLVM_FUZZER_MERGE_H
