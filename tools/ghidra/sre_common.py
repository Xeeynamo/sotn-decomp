import collections

# Shared types between Ghidra's Jython and rec2's Pythoh scripts

class FunctionArgument:
    def __init__(self, type, name):
        self.type = type
        self.name = name

    def asdict(self):
        return {
            "type": self.type,
            "name": self.name,
        }

    @classmethod
    def fromdict(cls, dkt):
        return cls(**dkt)

class FunctionDetails:
    def __init__(self, rettype, callconv, name, arguments, noreturn, vararg):
        self.rettype = rettype
        self.callconv = callconv
        self.name = name
        self.arguments = arguments
        self.noreturn = noreturn
        self.vararg = vararg

    def asdict(self):
        return {
            "rettype" : self.rettype,
            "callconv" : self.callconv,
            "name" : self.name,
            "arguments" : [arg.asdict() for arg in self.arguments],
            "noreturn" : self.noreturn,
            "vararg" : self.vararg,
        }

    @classmethod
    def fromdict(cls, dkt):
        dkt2 = {
            "rettype": dkt["rettype"],
            "callconv": dkt["callconv"],
            "name": dkt["name"],
            "arguments": list(FunctionArgument(**arg) for arg in dkt["arguments"]),
            "noreturn": dkt["noreturn"],
            "vararg": dkt["vararg"],
        }
        return cls(**dkt2)

class FunctionHookItem:
    def __init__(self, address, name, funcdef, details):
        self.address = address
        self.name = name
        self.funcdef = funcdef
        self.details = details

    def asdict(self):
        return {
            "address" : self.address,
            "name" : self.name,
            "funcdef" : self.funcdef,
            "details" : self.details.asdict(),
        }

    @classmethod
    def fromdict(cls, dkt):
        dkt2 = {
            "address" : dkt["address"],
            "name" : dkt["name"],
            "funcdef" : dkt["funcdef"],
            "details" : FunctionDetails.fromdict(dkt["details"]),
        }
        return cls(**dkt2)


VariableHookItem = collections.namedtuple("VariableHookItem", ("address", "vartype", "varname"))
VariableArrayHookItem = collections.namedtuple("VariableArrayHookItem", ("address", "vartype", "varname", "varcount"))

