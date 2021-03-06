#ifndef REF_SEQ_CONSTRUCTOR_HPP
#define REF_SEQ_CONSTRUCTOR_HPP


#include <sparsepp/spp.h>

#include "Util.hpp"
#include "CanonicalKmer.hpp"
#include <stack>

/*enum Task {
           SUCCESS,
           FAILURE
};
*/

enum SearchType {
  PREDECESSOR,
  SUCCESSOR
};

struct nextCompatibleStruct {
  size_t cid;
  size_t tpos ;
  uint32_t cpos ;
  bool isCurContigFw ;

  nextCompatibleStruct(size_t cntgIn, size_t tposIn, uint32_t cposIn, bool mFw) : cid(cntgIn), tpos(tposIn), cpos(cposIn), isCurContigFw(mFw) {} 
} ;

struct strInfo {
  size_t pid;
  std::string str;
  bool shouldAppend;
};


template <typename PufferfishIndexT>
class RefSeqConstructor {

public:
  RefSeqConstructor(PufferfishIndexT* pfi, spp::sparse_hash_map<uint32_t, util::ContigBlock>* contigSeqCache);
  std::string fillSeq(size_t tid,
                                               size_t tpos,
                                               bool isCurContigFw,
                                               util::ContigBlock& curContig,
                                               uint32_t startp,
                                               util::ContigBlock& endContig,
                                               uint32_t endp,
                                               bool isEndContigFw,
                                               uint32_t txpDist);
  /* Task doBFS(size_t tid,
             size_t tpos,
             bool isCurContigFw,
             util::ContigBlock& curContig,
             size_t startp,
             util::ContigBlock& endContig,
             bool isEndContigFw,
             uint32_t threshold,
             std::string& seq);
  */
  std::string doDFS(size_t tid,
             size_t tpos,
             bool isCurContigFw,
             util::ContigBlock& curContig,
             uint32_t startp,
             util::ContigBlock& endContig,
             bool isEndContigFw,
             uint32_t threshold);


  /*  //search predecessors
  Task fillSeqLeft(size_t tid,
                   size_t tpos,
                   util::ContigBlock& curContig,
                   bool isCurContigFw,
                   uint32_t cstart,
                   std::string& seq);

  Task doRevBFS(size_t tid,
                size_t tpos,
                util::ContigBlock& curContig,
                bool isCurContigFw,
                uint32_t cstart,
                uint32_t threshold,
                std::string& seq);
  */
private:
  PufferfishIndexT* pfi_ ;
  size_t k ;
  spp::sparse_hash_map<uint32_t, util::ContigBlock>* contigSeqCache_;



  size_t remainingLen(util::ContigBlock& contig, size_t startp, bool isCurContigFw, bool fromTheEnd);
  void append(std::string& seq, util::ContigBlock& contig, size_t startp, size_t endp, bool isCurContigFw);
  std::pair<std::string, bool> appendByLen(util::ContigBlock& contig, size_t startp, size_t len, bool isCurContigFw, bool appendSuffix);
  //TODO 
  //void prependByLen(std::string& seq, util::ContigBlock& contig, size_t startp, size_t len, bool isCurContigFw, bool appendSuffix);
  std::string getRemSeq(util::ContigBlock& contig, size_t len, bool isCurContigFw, bool appendSuffix);
  void cutoff(std::string& seq, size_t len);
  std::string rc(std::string str);
  char rev(const char& c);
  std::vector<nextCompatibleStruct> fetchSuccessors(util::ContigBlock& contig,
                                                 bool isCurContigFw,
                                                 size_t tid,
                                                    size_t tpos,
                                                    size_t txpDist);
  /*  std::vector<nextCompatibleStruct> fetchPredecessors(util::ContigBlock& contig,
                                                    bool isCurContigFw,
                                                    size_t tid,

                                                    size_t tpos);
  */
};

#endif
