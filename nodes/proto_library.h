// Copyright 2013
// Author: Christopher Van Arsdale

#ifndef _REPOBUILD_NODES_PROTO_LIBRARY_H__
#define _REPOBUILD_NODES_PROTO_LIBRARY_H__

#include <string>
#include <vector>
#include "repobuild/nodes/node.h"

namespace repobuild {

class ProtoLibraryNode : public Node {
 public:
  ProtoLibraryNode(const TargetInfo& t,
                   const Input& i)
      : Node(t, i),
        gen_node_(NULL),
        cc_node_(NULL),
        java_node_(NULL),
        go_node_(NULL),
        py_node_(NULL) {
  }
  virtual ~ProtoLibraryNode() {}
  virtual void Parse(BuildFile* file, const BuildFileNode& input);
  virtual void LocalWriteMake(Makefile* out) const {
    WriteBaseUserTarget(out);
  }

 private:
  void FindProtoPrefixes(const std::vector<Resource>& input_files,
                         std::vector<Resource>* prefixes) const;

  void GenerateGo(const std::vector<Resource>& input_prefixes,
                  std::vector<std::string>* outputs,
                  BuildFile* file);
  void GenerateCpp(const std::vector<Resource>& input_prefixes,
                   std::vector<std::string>* outputs,
                   BuildFile* file);
  void GeneratePython(const std::vector<Resource>& input_prefixes,
                      std::vector<std::string>* outputs,
                      BuildFile* file);
  void GenerateJava(BuildFile* file,
                    const BuildFileNode& input,
                    const std::vector<Resource>& input_prefixes,
                    const std::vector<std::string>& java_classnames,
                    std::vector<std::string>* outputs);
  virtual bool IncludeChildDependency(DependencyCollectionType type,
                                      LanguageType lang,
                                      Node* node) const;

  Node* gen_node_;
  Node* cc_node_;
  Node* java_node_;
  Node* go_node_;
  Node* py_node_;
};

}  // namespace repobuild

# endif  // _REPOBUILD_NODES_PROTO_LIBRARY_H__
