// Helper schema code for CCM command code generator
local moo = import "moo.jsonnet";
local cg = moo.schema.avro.codegen;

// Return a function which looks like a concrete schema but is
// actually many concrete schema.  When returned function is
// itself called an a domain schema, call each concrete schema on
// the domain and return the result as a flat array.
local multischema(ss) = function(schemalist) {
    types: std.flattenArrays([s(schemalist).types for s in ss])
};


{
    // Return a concrete domain schema (avro) which may then be
    // applied to templates in order to generate code.  The name used
    // in various places including to form file names.
    codegen(name, namespace, schemalist) :: 
    cg(name, multischema(schemalist), namespace) + {
        // NB: adjust this if the generated headers are considered
        // public.
        structinc: '#include "%s-structs.hpp"'%name,
        anyincludes: "#include <nlohmann/json.hpp>",
        anytype: "nlohmann::json",
    },
}

