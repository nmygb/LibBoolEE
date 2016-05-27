#include "LibBoolEE.hpp"
#include "LibBoolEE.h"

#define CPP_TEST(expr, vals) \
	if(!LibBoolEE::resolve(expr,vals)){ \
		throw std::runtime_error(std::string(expr) + " does not yield the expected value in Cpp test.\n"); \
	};

#define C_TEST(expr, vals, len) \
	if(!LibBoolEEResolve(expr,vals, len)){ \
		throw std::runtime_error(std::string(expr) + " does not yield the expected value in C test.\n"); \
	};

int main() {
	// Test the library via Cpp interface
    LibBoolEE::Vals vals;
    vals.insert(std::make_pair("A", true));
    vals.insert(std::make_pair("B", false));
	CPP_TEST("A", vals);
	CPP_TEST("A|B", vals);
	CPP_TEST("!(A&B)", vals);
	CPP_TEST("(!B&A)", vals);
	CPP_TEST("(A&B&B&A)|A|B", vals);
	CPP_TEST(("!(\n(A&B ) \t | (B&A)|!(A|B))"), vals); // Whitespace
	CPP_TEST("A|B&B", vals); // operator precedence
	CPP_TEST("!((A|B)&B)", vals); // operator precedence - cont'd
	CPP_TEST("!(!B&!A|A&B)", vals); // the negation error

	// Test the C interface
	LibBoolEEVal c_vals [2];
	c_vals[0].name = "A";
	c_vals[0].value = true;
	c_vals[1].name = "B";
	c_vals[1].value = false;
	C_TEST("A|B", c_vals, 2);
}