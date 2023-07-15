from pycparser import c_parser, c_ast
import pprint
from deepdiff import DeepDiff

# class FunctionVisitor(c_ast.NodeVisitor):
#     def __init__(self):
#         self.function_declarations = []

#     def visit_FuncDef(self, node):
#         if isinstance(node.decl.type, c_ast.FuncDecl):
#             func_name = node.decl.name
#             ret_type = node.decl.type.type.names[0]
#             args = []

#             if node.decl.type.args:
#                 for param_decl in node.decl.type.args.params:
#                     param_type = param_decl.type.type.names[0]
#                     param_name = param_decl.name
#                     args.append({"type": param_type, "name": param_name})

#             func_def = {
#                 "name": func_name,
#                 "rettype": ret_type,
#                 "arguments": args
#             }

#             self.function_declarations.append(func_def)

class FunctionVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.function_declarations = []

    def visit_FuncDef(self, node):

        # is this a function decleration?
        if isinstance(node.decl.type, c_ast.FuncDecl):

            return_type = None
            # print(node.decl.type.type)
            # exit()


            # if isinstance(node.decl.type.type, c_ast.IdentifierType):
            #     if node.decl.type.type.names[0] == "void":
            #         return_type = "void"
            if isinstance(node.decl.type.type, c_ast.PtrDecl):
                return_type = node.decl.type.type.type.type.names[0]
                return_type = return_type + "*"
            elif node.decl.type.type.type.names[0] == "void":
                return_type = "void"
            
            # print(return_type + "*")
            # print(node.decl.type.type)
            # exit()
            # get the function name
            print("function_name:", node.decl.name)
            func_name = node.decl.name

            args = []

            # get the parameters

            if node.decl.type.args.params[0].type.type.names[0] == 'void':
                # void arguments
                # leave it empty
                pass
            else:
                for arg in node.decl.type.args:
                    print(arg.type.type.names[0], arg.type.declname)
                    args.append({"type": arg.type.type.names[0],
                                "name": arg.type.declname})

            func_def = {
                "name": func_name,
                "rettype": return_type,
                "arguments": args
            }

            # print(func_def)
            # exit()
            self.function_declarations.append(func_def)

            # print(node.decl.type.args)
            # exit()
            # func_name = node.decl.name
            # ret_type = None
            # args = []

            # if isinstance(node.decl.type.type, c_ast.TypeDecl):
            #     ret_type = node.decl.type.type.declname
            # elif isinstance(node.decl.type.type, c_ast.IdentifierType):
            #     ret_type = ' '.join(node.decl.type.type.names)



# class FuncDef(Node):
#     __slots__ = ('decl', 'param_decls', 'body', 'coord', '__weakref__')
#     def __init__(self, decl, param_decls, body, coord=None):
#         self.decl = decl
#         self.param_decls = param_decls
#         self.body = body
#         self.coord = coord

            # if node.decl.type.args:
            #     for param_decl in node.decl.type.args.params:
            #         param_type = None
            #         param_name = None 
            #         if param_name is not None:
            #             param_name = param_decl.name
            #         if isinstance(param_decl.type, c_ast.TypeDecl):
            #             param_type = param_decl.type.declname
            #         elif isinstance(param_decl.type, c_ast.IdentifierType):
            #             param_type = ' '.join(param_decl.type.names)
            #         args.append({"type": param_type, "name": param_name})

            # func_def = {
            #     "name": func_name,
            #     "rettype": ret_type,
            #     "arguments": args
            # }

            # self.function_declarations.append(func_def)


def parse_code(code):
    parser = c_parser.CParser()
    ast = parser.parse(code)

    visitor = FunctionVisitor()
    visitor.visit(ast)

    return visitor.function_declarations

def make_funcdef(declaration):
    args = ""

    print(declaration)
    for arg in declaration["arguments"]:
        arg_type = arg["type"]
        arg_name = arg["name"]

        if arg == declaration["arguments"][len(declaration["arguments"]) - 1]:
            args = args + f"{arg_type} {arg_name}"
        else:
            args = args + f"{arg_type} {arg_name},"

    if len(declaration["arguments"]) == 0:
        args = "void"
    return f"{declaration['rettype']} {declaration['name']}({args})"

def format_function_declaration(declaration):
    formatted_declaration = {
        "address": 4507024,  # Replace with the appropriate address
        "name": declaration["name"],
        "funcdef": make_funcdef(declaration),
        "details": {
            "rettype": declaration["rettype"],
            "callconv": "cdecl",
            "name": declaration["name"],
            "arguments": declaration["arguments"],
            "noreturn": False,
            "vararg": False  # Set this appropriately based on your requirements
        }
    }

    return formatted_declaration


get_equip_count = """
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

u8* GetEquipCount(s32 equipTypeFilter)
{
    return 0;
}
"""
void = """
void OpenDiagnostics(void)
{
}
"""
def run_test(the_code, expected):
    function_declarations = parse_code(the_code)

    formatted_declarations = []
    for declaration in function_declarations:
        formatted_declaration = format_function_declaration(declaration)
        formatted_declarations.append(formatted_declaration)

    
    # pprint.pprint(formatted_declarations)
    # print(declaration.__dict__.items() ^ expected.__dict__.items())
    # differences = DeepDiff(declaration, expected)



    print("====================MINE")
    pprint.pprint(formatted_declarations[0])
    # print("====================EXPECTED")
    # pprint.pprint(expected)
    # print("decl", differences)
    assert(formatted_declarations[0] == expected)


equip_expected = {'address': 4507024,
  'details': {'arguments': [{'name': 'equipTypeFilter', 'type': 's32'}],
              'callconv': 'cdecl',
              'name': 'GetEquipCount',
              'noreturn': False,
              'rettype': 'u8*',
              'vararg': False},
  'funcdef': 'u8* GetEquipCount(s32 equipTypeFilter)',
  'name': 'GetEquipCount'}

run_test(get_equip_count, equip_expected)

void_expected = {
            "address": 4507024,
            "name": "OpenDiagnostics",
            "funcdef": "void OpenDiagnostics(void)",
            "details": {
                "rettype": "void",
                "callconv": "cdecl",
                "name": "OpenDiagnostics",
                "arguments": [],
                "noreturn": False,
                "vararg": False
            }
        }
run_test(void, void_expected)
