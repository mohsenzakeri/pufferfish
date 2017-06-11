#include "FatPufferGraph.hpp"
//#include "OurGFAReader.hpp"
//#include "semiCompactedCompactor.hpp"
#include "GFAConverter.hpp"

int main(int argc, char* argv[]){
  (void)argc;
	std::string gfa_infilename = argv[1] ;
	std::string gfa_outfilename = argv[2];

	short k = 31;
	GFAConverter gc(argv[1], k);
	gc.parseFile();
	gc.randomWalk();
	gc.writeFile(argv[2]);
/*	PosFinder pf(argv[1], k);
	pf.parseFile();
	
	SemiCompactedCompactor scc(pf.getNewSegments(), 
						  pf.getContigNameMap(),
						  pf.getPathStart(),
						  pf.getPathEnd(),
						  pf.getSemiCG(),
						  k);
	scc.compact();
	scc.updatePath(pf.getPaths());
	scc.writeFile(gfa_outfilename);
*/

	return 0 ;
}
