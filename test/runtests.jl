using Test
using ReferenceTests

cppfiles = filter(readdir("../", join=true)) do f
	last(splitext(f)) == ".cpp"
end

for fname in cppfiles
	@testset "$(fname)" begin
		mktempdir() do d
			exec = joinpath(d, first(splitext(fname)))
			run(`g++ -O2 -std=c++17 -DUNIT_TEST $(fname) -o $(exec)`)
			o = read(`$(exec)`, String)
			@test_reference "$(basename(fname)).txt" o
		end
	end
end