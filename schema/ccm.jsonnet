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
    codegen(Name, namespace, schemalist) :: 
    cg(Name, multischema(schemalist), namespace) + {
        // NB: adjust this if the generated headers are considered
        // public.
        structincs: '#include "%sStructs.hpp"'%Name,
        anyincludes: "#include <nlohmann/json.hpp>",
        anytype: "nlohmann::json",
    },

    // This collects all meta info about CCM commands intended for use
    // in other parts of the schema.
    commands: {
        Names: ["Exec","Init","Conf","Start","Stop","Scrap","Fina","Term","Undef"],
        names: [std.asciiLower(n) for n in self.Names],
    },

    // fixme: describe an fsm, add template to realize it.  Assume boost::msm.
}

