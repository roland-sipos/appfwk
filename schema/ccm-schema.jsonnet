// Interface to CCM schema.
//
// User schema may import this module to reuse parts.

local moo = import "moo.jsonnet";
local re = moo.schema.re;

function(schema) {

    // An "ident" is a string with a limited "spelling".  It should be
    // used for instance names or implementation names registered with
    // a factory.
    ident: schema.string("Ident", pattern=re.ident),

    // A string consiting of a single letter
    letter: schema.string("Letter", pattern='^[a-zA-Z]$'),

    // A string that is a legal file path
    filepath: schema.string("FilePath", pattern=re.hierpath),

    // A Boolean value 
    bool: schema.boolean("Bool"),

    // A double precision floating piont number
    double: schema.number("Double", dtype="f8"),

    // A single precision floating piont number
    float: schema.number("Float", dtype="f4"),

    // A two byte int
    short: schema.number("Short", dtype="i2"),

    // A four byte int
    int: schema.number("Int", dtype="i4"),

    // An eight byte int
    long: schema.number("Long", dtype="i8"),

    // CCM commands and command dispatch protocol.
    //
    // A CCM command is consumed by a process (eg DAQProcess).  The
    // command has a name and a payload.  For appfwk processes, the
    // payload is structured as a map of recipients of command data.
    // A recipient is some named process-dependent substructure (eg,
    // DAQProcess has named DAQModule instances).  The recipient may
    // be an empty string in which case the process should intrepret
    // the corresponding payload to apply to the process as a whole
    // (or eg to all substructure equivalently).  As the leaf command
    // data must be interpreted in a particular context, its
    // representation in the general context is left as an "any".
    // Additional schema may be applied in the specific contexts.  For
    // this to work obviously relies on colusion in how the schema are
    // interprted.  We describe the schema for these individual parts:

    // Every CCM command has a name from a fixed set. 
    cmdname: schema.enum(
        "CommandName",
        ["exec","init","conf","start","stop","scrap","fini","term","undef"],
        default="undef",
        doc="The set of command names which may be expected from CCM"),
    
    // The command recipient is either an empty string (applies to
    // "all" of the process in parts or whole) or names substructure
    // of the process.
    cmdrecipient: schema.string("CommandRecipient",
                                pattern='^$|%s' % self.ident),

    // Command data is what a recipient gets.  In the general context,
    // its precise schema is unknown and so it is represented as an
    // "any".  Other schema may be applied in a more specific context
    // to resolve any ambiguity.
    cmddata: schema.any("CommandData"),

    // The command payload is the object mapping recipients to their
    // data.
    cmdpayload: schema.record("CommandPayload", fields = [
        schema.field("recipient", $.cmdrecipient, "",
                      doc="Recipient of command data"),
        schema.field("data", $.cmddata, {},
                     doc="Command data")
    ], doc="Associate data to a recipient"),
    cmdpayloads: schema.sequence("CommandPayloads", $.cmdpayload),

    command: schema.record("Command", fields = [
        schema.field("name", $.cmdname, "undef", doc="The command name"),
        schema.field("payload", $.cmdpayloads, [], doc="The command payloads")
    ], doc="A CCM command to a process"),

    types: [$.ident, $.letter, $.filepath, $.bool, $.short, $.int, $.long, $.float, $.double,
            $.cmdname, $.cmdrecipient, $.cmddata, $.cmdpayload, $.cmdpayloads, $.command],
}
