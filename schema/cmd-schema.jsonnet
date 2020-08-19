// Interface to CCM schema.
//
// User schema may import this module to reuse parts.

local moo = import "moo.jsonnet";
local re = moo.schema.re;
local ccm = import "ccm.jsonnet";

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
    ulong: schema.number("Long", dtype="u8"),

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

    // Every CCM command has an ID number/enum. 
    id: schema.enum(
        "Id",
        ccm.commands.names,
        default="undef",
        doc="The set of expected command identifiers"),
    
    // The command recipient is either an empty string (applies to
    // "all" of the process in parts or whole) or names substructure
    // of the process.
    recipient: schema.string("Recipient",
                             pattern='^$|%s' % self.ident),

    // Command data is what a recipient gets.  In the general context,
    // its precise schema is unknown and so it is represented as an
    // "any".  Other schema may be applied in a more specific context
    // to resolve any ambiguity.
    data: schema.any("Data"),

    // The command payload is the object mapping recipients to their
    // data.
    payload: schema.record("Payload", fields = [
        schema.field("recipient", $.recipient, "",
                      doc="Recipient of command data"),
        schema.field("data", $.data, {},
                     doc="Command data")
    ], doc="Associate data to a recipient"),
    payloads: schema.sequence("Payloads", $.payload),

    // Wrap everything up into a single object.
    object: schema.record("Object", fields = [
        schema.field("id", $.id, "undef", doc="The command ID number"),
        schema.field("payload", $.payloads, [], doc="The command payloads")
    ], doc="A command to a process"),


    // The appfwk inserts an FSM between command source and command
    // execution in order to protect the process from unknown commands
    // or unexpected ordering.  Each FSM event must be of a specific
    // (C++) type so we make a set of little structs.

    fsmevts: [schema.record(N, fields = [
        schema.field("id", $.id, "Id::"+std.asciiLower(N), doc="Command ID number"),
        schema.field("payload", $.payload, doc="Command payload data"),
    ], doc="FSM event type for command "+N) for N in ccm.commands.Names],

    types: [$.ident, $.letter, $.filepath, $.bool, $.short, $.int, $.long, $.float, $.double,
            $.id, $.recipient, $.data, $.payload, $.payloads, $.object] + self.fsmevts,
}
