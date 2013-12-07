include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
	)

BISON_TARGET(ClReader ClReader.y ${CMAKE_CURRENT_BINARY_DIR}/ClReader.cc)
FLEX_TARGET(ClReader-lex ClReader.l ${CMAKE_CURRENT_BINARY_DIR}/ClReader-lex.cc)
ADD_FLEX_BISON_DEPENDENCY(ClReader-lex ClReader)

set(cassowary_sources
	ClAbstractVariable.cc
	ClConstraint.cc
	ClLinearExpression.cc
	ClSolver.cc
	ClSimplexSolver.cc
	ClStrength.cc
	ClSymbolicWeight.cc
	ClTableau.cc
	ClVariable.cc
	ClFloatVariable.cc
	ClSlackVariable.cc
	ClDummyVariable.cc
	${FLEX_ClReader-lex_OUTPUTS}
	${BISON_ClReader_OUTPUTS}
	ClC.cc
)

add_library(cassowary ${cassowary_sources})
