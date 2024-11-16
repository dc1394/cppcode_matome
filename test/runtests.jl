using Test
using ReferenceTests

cppfiles = filter(readdir("../", join=true)) do f
	last(splitext(f)) == ".cpp"
end

for fname in cppfiles
	# omp.h
	basename(fname) == "Twitter_240420_2.cpp" && continue
	basename(fname) == "Twitter_240430.cpp" && continue

	# too long to run
	basename(fname) == "Twitter_240507_2.cpp" && continue
	# debug
	basename(fname) == "Twitter_240505.cpp" && continue

	@testset "$(fname)" begin
		mktempdir() do d
			exec = joinpath(d, basename(first(splitext(fname))))
			run(`g++ -O2 -std=c++20 -DSAVE_RESULT=0 -DTEST $(fname) -o $(exec)`)
			o = read(`$(exec)`, String)
			reftxt = "$(first(splitext(basename(fname)))).txt"
			@test_reference reftxt o
		end
	end
end
