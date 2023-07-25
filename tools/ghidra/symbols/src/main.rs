// extern crate lang_c;
// use lang_c::driver::{Config, parse}; 
// use lang_c::span::Node;
// // pub fn translate(
// //     tu: lang_c::ast::TranslationUnit,
// //     ec: &mut ErrorCollector,
// // ) -> Result<Self, ()> {
// //     let mut r = Self {
// //         scope: NameScope::new(),
// //         functions: Vec::new(),
// //     };
// //     let mut has_error = false;
// //     for Node { node: ed, .. } in tu.0.into_iter() {
// //         match ed {
// //             ExternalDeclaration::StaticAssert(node) => {
// //                 constant::check_static_assert(node, &mut r.scope, ec)?;
// //             }
// //             ExternalDeclaration::Declaration(n) => {
// //                 if r.add_declaration(n, ec).is_err() {
// //                     has_error = true;
// //                 }
// //             }
// //             ExternalDeclaration::FunctionDefinition(n) => {
// //                 if r.add_function_definition(n, ec).is_err() {
// //                     has_error = true;
// //                 }
// //             }
// //         }
// //     }
// //     if has_error {
// //         Err(())
// //     } else {
// //         Ok(r)
// //     }
// // }
// use lang_c::ast::ExternalDeclaration;
// use lang_c::ast::DeclarationSpecifier;
// use lang_c::ast::FunctionSpecifier;
// use lang_c::ast::DeclaratorKind;
// use lang_c::ast::Identifier;

// fn handle_type_specifier(spec: Node<lang_c::ast::TypeSpecifier>)
// {
//     use lang_c::ast::TypeSpecifier;
//     let span = spec.span;
//     let spec = spec.node;
//     match spec {
//         TypeSpecifier::Void => unimplemented!("atomic"),
//         TypeSpecifier::Char => {
//             println!("TypeSpecifier::Char {:?}", spec);
//         },
//         TypeSpecifier::Int =>  {
//             println!("TypeSpecifier::{:?}", spec);
//         },
//         TypeSpecifier::Float => unimplemented!("atomic"),
//         TypeSpecifier::Double => unimplemented!("atomic"),
//         TypeSpecifier::Bool => unimplemented!("atomic"),
//         TypeSpecifier::Signed => {
//             println!("TypeSpecifier::Signed {:?}", spec);
//         },
//         TypeSpecifier::Unsigned =>  {
//             println!("TypeSpecifier::{:?}", spec);
//         },
//         TypeSpecifier::Long =>  {
//             println!("TypeSpecifier::{:?}", spec);
//         },
//         TypeSpecifier::Short => {
//             println!("TypeSpecifier::{:?}", spec);
//         },
//         TypeSpecifier::TypedefName(n) => {
//             // println!("skipping typedef name {:?}", n)
//             println!("TypeSpecifier::TypedefName {:?}", n.node.name);
//         },
//         TypeSpecifier::Struct(s) => unimplemented!("atomic"),
//         TypeSpecifier::Enum(_) => todo!(),
//         TypeSpecifier::TypeOf(_) => todo!(),
//         TypeSpecifier::Atomic(_) => unimplemented!("atomic"),
//         TypeSpecifier::Complex => unimplemented!("complex"),
//         TypeSpecifier::TS18661Float(_) => unimplemented!("TS 18551 float"),
//     }
// }
// use lang_c::ast::FunctionDefinition;
// use std::process::exit;

// fn handle_function_definition(n : Node<FunctionDefinition>)
// {
// //     println!("{:#?}",n);
// //     exit(0);
//     // println!("{:#?}", n.node.specifiers[0].node);

//     for declspec in n.node.specifiers {
//         match declspec.node {
//             DeclarationSpecifier::StorageClass(stc) => {
//                 unimplemented!();
//                 // if storage_class.is_none() {
//                 //     storage_class = Some(stc);
//                 // } else {
//                 //     ec.record_error(CompileError::MultipleStorageClasses, stc.span)?;
//                 // }
//             }
//             DeclarationSpecifier::Function(f) => match f.node {
//                 FunctionSpecifier::Inline => unimplemented!(),
//                 FunctionSpecifier::Noreturn => unimplemented!(),
//             },
//             DeclarationSpecifier::TypeSpecifier(ts) => {

//                 handle_type_specifier(ts);
//                 // type_builder.add_type_specifier_node(ts, scope, ec)?
//                 // println!("ts: {:#?}",ts);
//             }
//             DeclarationSpecifier::TypeQualifier(q) => {
//                 unimplemented!();
//                 // type_builder.add_type_qualifier_node(q, ec)?
//             }
//             DeclarationSpecifier::Alignment(_) => unimplemented!(),
//             DeclarationSpecifier::Extension(_) => unimplemented!(),
//         }
//     }

//     // ignore statements

//     println!("{:?}", n.node.declarator.node.kind.node);

//     // println!("{:?}", n.node.declaratior.node.derived.node)

//     for node in n.node.declarator.node.derived {
//         match node {
//             Pointer => {
//                 println!("*");
//             },
//             // Function => {
//             //     // println!("Function");
//             //     unimplemented!();
//             // }
//         }
//     }

//     // get function name
//     match n.node.declarator.node.kind.node {
//         DeclaratorKind::Abstract => unimplemented!(),
//         DeclaratorKind::Identifier(id_node) => {
//             println!("{:?}", id_node.node);

//             match id_node.node {
//                 Identifier { name } => {
//                     println!("{:?}", name);
//                 }
//             }
//         },
//         DeclaratorKind::Declarator(box_node_declarator) => unimplemented!()
//     }

//     // let thing = ;
//     // match n.node.specifiers[0].node {
//     //     DeclarationSpecifier::TypeSpecifier => {
//     //         println!("{:#?}",n.node.specifiers[0].node);
//     //     }
//     // }
//     // if r.add_function_definition(n, ec).is_err() {
//     //     has_error = true;
//     // }

// }

// fn main() {
//     let config = Config::default();
//     let parsed = parse(&config, "example.c");

//     for Node { node: ed, .. } in parsed.unwrap().unit.0.into_iter() {
//         match ed {
//             ExternalDeclaration::StaticAssert(node) => {
//                 unimplemented!();
//                 // constant::check_static_assert(node, &mut r.scope, ec)?;
//             }
//             ExternalDeclaration::Declaration(n) => {
//                 // println!("{:#?}",n);
//                 // // unimplemented!();

//                 // for declspec in n.node.specifiers {
//                 //     match declspec.node {
//                 //         DeclarationSpecifier::StorageClass(stc) => {
//                 //             println!("{:#?}",stc);
//                 //             // unimplemented!();
//                 //             // if storage_class.is_none() {
//                 //             //     storage_class = Some(stc);
//                 //             // } else {
//                 //             //     ec.record_error(CompileError::MultipleStorageClasses, stc.span)?;
//                 //             // }
//                 //         }
//                 //         DeclarationSpecifier::Function(f) => match f.node {
//                 //             FunctionSpecifier::Inline => unimplemented!(),
//                 //             FunctionSpecifier::Noreturn => unimplemented!(),
//                 //         },
//                 //         DeclarationSpecifier::TypeSpecifier(ts) => {

//                 //             handle_type_specifier(ts);
//                 //             // type_builder.add_type_specifier_node(ts, scope, ec)?
//                 //             // println!("ts: {:#?}",ts);
//                 //         }
//                 //         DeclarationSpecifier::TypeQualifier(q) => {
//                 //             unimplemented!();
//                 //             // type_builder.add_type_qualifier_node(q, ec)?
//                 //         }
//                 //         DeclarationSpecifier::Alignment(_) => unimplemented!(),
//                 //         DeclarationSpecifier::Extension(_) => unimplemented!(),
//                 //     }
//                 // }
//                 // // if r.add_declaration(n, ec).is_err() {
//                 // //     has_error = true;
//                 // // }
//             }
//             ExternalDeclaration::FunctionDefinition(n) => {
//                 handle_function_definition(n);
//             }
//         }
//     }
    
//     // println!("{:#?}",);
// }

// // // fn main() {
// // //     println!("Hello, world!");
// // // }

// // extern crate lang_c;

// // use lang_c::driver::parse_translation_unit;
// // use lang_c::span::Node;

// // fn parse_code(code: &str) -> Result<Vec<Node>, lang_c::driver::Error> {
// //     parse_translation_unit(code)
// // }

// // fn format_function_declaration(declaration: &Node) -> serde_json::Value {
// //     let function_name = declaration
// //         .clone()
// //         .expect("Failed to clone declaration")
// //         .into_inner()
// //         .expect("Failed to retrieve inner declaration")
// //         .into_declaration()
// //         .expect("Failed to convert to declaration")
// //         .name
// //         .expect("Failed to retrieve function name");

// //     let function_type = declaration
// //         .clone()
// //         .expect("Failed to clone declaration")
// //         .into_inner()
// //         .expect("Failed to retrieve inner declaration")
// //         .into_declaration()
// //         .expect("Failed to convert to declaration")
// //         .decl
// //         .into_function()
// //         .expect("Failed to retrieve function declaration");

// //     let ret_type = function_type.ret_type;
// //     let arguments = function_type
// //         .params
// //         .into_iter()
// //         .map(|param| {
// //             let param_type = param.decl.type_name;
// //             let param_name = param.decl.name.expect("Failed to retrieve parameter name");
// //             serde_json::json!({
// //                 "type": param_type,
// //                 "name": param_name,
// //             })
// //         })
// //         .collect::<Vec<_>>();

// //     let formatted_declaration = serde_json::json!({
// //         "name": function_name,
// //         "rettype": ret_type,
// //         "arguments": arguments,
// //     });

// //     formatted_declaration
// // }

// // fn main() {
// //     let code = r#"
// //         void dr_dprintf(const char* fmt_string, ...);
// //     "#;

// //     match parse_code(code) {
// //         Ok(nodes) => {
// //             let mut formatted_declarations = Vec::new();
// //             for node in nodes {
// //                 if let Some(declaration) = node.into_inner().and_then(|inner| inner.into_declaration()) {
// //                     let formatted_declaration = format_function_declaration(&declaration);
// //                     formatted_declarations.push(formatted_declaration);
// //                 }
// //             }
// //             println!("{}", serde_json::to_string_pretty(&formatted_declarations).unwrap());
// //         }
// //         Err(e) => {
// //             eprintln!("Parsing error: {:?}", e);
// //         }
// //     }
// // }




// extern crate lang_c;

use lang_c::ast as parse_ast;
use lang_c::driver::{parse_preprocessed, Config};
// use lang_c::print::Printer;
use lang_c::span::Span;
// use lang_c::visit::*;
use std::process::Command;
// use crate::ast::Tree;
// use crate::definitions::{AstRelation, ID};

pub fn parse_file_into_ast(file_path: &String) -> Vec<MyFunc>  {
    parse_with_lang_c(file_path)
}

fn parse_with_lang_c(file_path: &String) -> Vec<MyFunc>  {
    let mut config = Config::default();

    let output = Command::new("cpp")
        .args(&["-P", "-E", "-D", "GHIDRA", file_path])
        .output()
        .expect("Failed to execute command");

    if output.status.success() {
        // let preprocessed_code = String::from_utf8(&output.stdout);


        match String::from_utf8(output.stdout) {
            Ok(s) => {

                // println!("Preprocessed code:\n{}", preprocessed_code);
                let lines: Vec<&str> = s.lines().take(30).collect();

                // for line in lines {
                //     println!("{}", line);
                // }
                for (i, line) in lines.iter().enumerate() {
                    let line_number = i + 1;
                    println!("Line {}: {}", line_number, line);
                }
                let parse_output = parse_preprocessed(&config, s);
                match parse_output {
                    Ok(parse) => {
                        // let s = &mut String::new();
                        // Printer::new(s).visit_translation_unit(&parse.unit);
                        // println!("{}", s);
                        let mut ast_builder = AstBuilder::new();
                        return AstBuilder::build_tree(&mut ast_builder, &parse.unit);
                    }
                    Err(e) => {
                        panic!("Error during parsing: {:?}", e)
                    }
                }

            },
            Err(e) => {
                panic!("Something wrong");
            }
            //Err(io::Error::new(io::ErrorKind::Other, e)),
        }




    } else {
        let error_message = String::from_utf8_lossy(&output.stderr);
        println!("Error occurred: {}", error_message);
    }

    return Vec::new();
}

#[derive(Clone, Debug, Default)]
struct MyArg
{
    typename: String,
    name: String,
    pointers: String
}

#[derive(Clone, Debug, Default)]
pub struct MyFunc
{
    return_type: String,
    function_name: String,
    args: Vec<MyArg>
}

struct AstBuilder {
    // tree: Tree,
    current_max_id: u64,
    function_declarations: Vec<MyFunc>,
    // current_function: String
    current_function: MyFunc
}
 use std::process::exit;
// Traverse the parser output creating internal AST tree while keeping IDs consistent between nodes and relations.
// Uses a pattern similar to the Visit module in lang_c.
impl<'a> AstBuilder {
    pub fn new() -> Self {
        Self {
            // tree: Tree::new(),
            current_max_id: 0,
            function_declarations: Vec::new(),
            current_function: MyFunc::default()
        }
    }

    pub fn build_tree(&mut self, node: &'a parse_ast::TranslationUnit) -> Vec<MyFunc> {
        Self::visit_translation_unit(self, node);
        for func in self.function_declarations.clone().into_iter() {
            println!("{:#?}", func);
        }
        return self.function_declarations.clone();
    }

    // For now we will assume a single translation unit as root of tree.
    fn visit_translation_unit(&mut self, node: &'a parse_ast::TranslationUnit)  {
        let mut body_ids = vec![];
        for element in &node.0 {
            body_ids.push(self.visit_external_declaration(&element.node, &element.span));
        }
        let node_id = self.current_max_id;
        self.current_max_id = self.current_max_id + 1;
        // let relation = AstRelation::TransUnit {
        //     id: node_id,
        //     body_ids: body_ids.clone(),
        // };
        // // self.tree.add_root_node(node_id, relation);
        // // self.tree.replace_children(node_id, body_ids);
        // return // self.tree.clone();
    }

    // At the moment all declarations just traverse down to function definitions.
    fn visit_external_declaration(
        &mut self,
        node: &'a parse_ast::ExternalDeclaration,
        _span: &'a Span,
    )  {
        match *node {
            // No new node created here, just traverse.
            parse_ast::ExternalDeclaration::FunctionDefinition(ref f) => {
                self.visit_function_definition(&f.node, &f.span);
                // println!("{}", self.current_function);
            }
            _ => println!("visit_external_declaration skipping {:?}", *node),
        }
    }

    // A function definition results in multiple nodes.
    fn visit_function_definition(
        &mut self,
        node: &'a parse_ast::FunctionDefinition,
        _span: &'a Span,
    )  {
        // Get return type node ID (after creating node).
        // We are for now assuming that there is only a type specifier (in any case, it will just get the last specifier).
        let mut return_type_id = 0;
        for specifier in &node.specifiers {
             self.visit_declaration_specifier(&specifier.node, &specifier.span);
        }
        // Get function body compound ID (after creating node).
        let body_id = self.visit_statement(&node.statement.node, &node.statement.span);
        // We'll create the function definition node in the declarator since it hold most of the information.
        return self.visit_declarator_for_function(
            &node.declarator.node,
            &node.declarator.span
        );
    }
    fn visit_declaration_specifier(
        &mut self,
        node: &'a parse_ast::DeclarationSpecifier,
        _span: &'a Span,
    )  {
        match *node {
            parse_ast::DeclarationSpecifier::StorageClass(ref t) => {
                panic!("Feature not implemented");
                // return self.visit_type_specifier(&t.node, &t.span)
            }
            parse_ast::DeclarationSpecifier::TypeSpecifier(ref t) => {
                return self.visit_type_specifier(&t.node, &t.span)
            }
            parse_ast::DeclarationSpecifier::TypeQualifier(ref t) => {
                println!("skipping TypeQualifier");
                println!("{:#?} {:#?}", t, self.current_function);
                // panic!("Feature not implemented");
                // return self.visit_type_specifier(&t.node, &t.span)
            }
            parse_ast::DeclarationSpecifier::Function(ref t) => {
                panic!("Feature not implemented");
                // return self.visit_type_specifier(&t.node, &t.span)
            }
            parse_ast::DeclarationSpecifier::Alignment(ref t) => {
                panic!("Feature not implemented");
                // return self.visit_type_specifier(&t.node, &t.span)
            }
            parse_ast::DeclarationSpecifier::Extension(ref t) => {
                panic!("Feature not implemented");
                // return self.visit_type_specifier(&t.node)
            }
            _ => panic!("Feature not implemented"),
        }
    }

    fn visit_type_specifier(&mut self, node: &'a parse_ast::TypeSpecifier, _span: &'a Span) {
        match node {
            parse_ast::TypeSpecifier::TypedefName(typedef_name) => {

                // if this is the first it's the return type.

                if self.current_function.return_type == ""
                {
                    // let arg = MyArg {name:"unk".to_string(), typename:typedef_name.node.name.to_string()};
                    self.current_function.return_type.push_str(&typedef_name.node.name.to_string());
                }
                else {
                    let arg = MyArg {name:"unk".to_string(), typename:typedef_name.node.name.to_string(), pointers:"".to_string()};
                    self.current_function.args.push(arg);
                }


                // let mut arg = self.current_function.args.last().unwrap().typename.clone();
                // arg.push_str(&typedef_name.node.name);
                // self.current_function.args.last_mut().unwrap().typename = arg;
                //self.current_function.args.last().unwrap().typename.push_str(&typedef_name.node.name);
                let node_id = self.current_max_id;
                self.current_max_id = self.current_max_id + 1;
                // let relation = AstRelation::Void { id: node_id };
                // self.tree.add_node(node_id, relation);
                // return node_id;
            }
            parse_ast::TypeSpecifier::Void => {
                if self.current_function.return_type == ""
                {
                    // let arg = MyArg {name:"unk".to_string(), typename:typedef_name.node.name.to_string()};
                    self.current_function.return_type.push_str("void");
                }
                else {
                    let arg = MyArg {name:"unk".to_string(), typename:"void".to_string(), pointers:"".to_string()};
                    self.current_function.args.push(arg);
                }

                // println!("void");
                // exit(0);
                let node_id = self.current_max_id;
                self.current_max_id = self.current_max_id + 1;
                // let relation = AstRelation::Void { id: node_id };
                // self.tree.add_node(node_id, relation);
                // return node_id;
            }
            parse_ast::TypeSpecifier::Int => {
                if self.current_function.return_type == ""
                {
                    self.current_function.return_type.push_str("int");
                }
                else {
                    let arg = MyArg {name:"unk".to_string(), typename:"int".to_string(), pointers:"".to_string()};
                    self.current_function.args.push(arg);
                }
            }
            parse_ast::TypeSpecifier::Char => {
                if self.current_function.return_type == ""
                {
                    self.current_function.return_type.push_str("char");
                }
                else {
                    let arg = MyArg {name:"unk".to_string(), typename:"char".to_string(), pointers:"".to_string()};
                    self.current_function.args.push(arg);
                }
            }
            parse_ast::TypeSpecifier::Float => {
                let node_id = self.current_max_id;
                self.current_max_id = self.current_max_id + 1;
                // let relation = AstRelation::Float { id: node_id };
                // self.tree.add_node(node_id, relation);
                // return node_id;
            }
            _ => println!("visit_type_specifier skipping {:#?}", *node),
        }
    }

    fn visit_statement(&mut self, node: &'a parse_ast::Statement, _span: &'a Span) {
        return;
        match *node {
            parse_ast::Statement::Compound(ref c) => {
                let mut next_stmt_id = 0;
                let mut start_id = 0;
                let mut counter = 0;
                // We will traverse the compound backwards in order to link the block items.
                for item in c.iter().rev() {
                    let stmt_id = self.visit_block_item(&item.node, &item.span);
                    // Case: last item in compound.
                    if counter == 0 {
                        let node_id = self.current_max_id;
                        self.current_max_id = self.current_max_id + 1;
                        // let relation = AstRelation::EndItem {
                        //     id: node_id,
                        //     stmt_id,
                        // };
                        // self.tree.add_node(node_id, relation);
                        // self.tree.link_child(node_id, stmt_id);
                        next_stmt_id = node_id;
                        // Case: first item in compound (could also be last).
                        if counter == c.len() - 1 {
                            start_id = node_id;
                        }
                    } else {
                        let node_id = self.current_max_id;
                        self.current_max_id = self.current_max_id + 1;
                        // let relation = AstRelation::Item {
                        //     id: node_id,
                        //     stmt_id,
                        //     next_stmt_id,
                        // };
                        // self.tree.add_node(node_id, relation);
                        // self.tree.link_child(node_id, stmt_id);
                        // self.tree.link_child(node_id, next_stmt_id);
                        next_stmt_id = node_id;
                        // Case: first item in compound (could also be last).
                        if counter == c.len() - 1 {
                            start_id = node_id;
                        }
                    }
                    counter = counter + 1;
                }
                let node_id = self.current_max_id;
                self.current_max_id = self.current_max_id + 1;
                // let relation = AstRelation::Compound {
                //     id: node_id,
                //     start_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, start_id);
                // return node_id;
            }
            parse_ast::Statement::Expression(Some(ref e)) => {
                return self.visit_expression(&e.node, &e.span)
            }
            parse_ast::Statement::Return(Some(ref r)) => {
                let expr_id = self.visit_expression(&r.node, &r.span);
                let node_id = self.current_max_id;
                self.current_max_id = self.current_max_id + 1;
                // let relation = AstRelation::Return {
                //     id: node_id,
                //     expr_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, expr_id);
                // return node_id;
            }
            parse_ast::Statement::If(ref i) => {
                return self.visit_if_statement(&i.node, &i.span);
            }
            parse_ast::Statement::While(ref w) => {
                return self.visit_while_statement(&w.node, &w.span);
            }
            _ => {
                println!("{:?}", node);
                panic!("Feature not implemented");
            }
        }
    }

    fn visit_block_item(&mut self, node: &'a parse_ast::BlockItem, _span: &'a Span)  {
        match *node {
            parse_ast::BlockItem::Statement(ref s) => {
                return self.visit_statement(&s.node, &s.span)
            }
            parse_ast::BlockItem::Declaration(ref d) => {
                return self.visit_declaration(&d.node, &d.span)
            }
            _ => panic!("Feature not implemented"),
        }
    }

    // Currently just deals with normal assignments.
    fn visit_declaration(&mut self, node: &'a parse_ast::Declaration, _span: &'a Span)  {
        let mut type_id = 0;
        for specifier in &node.specifiers {
             self.visit_declaration_specifier(&specifier.node, &specifier.span);
        }
        return self.visit_init_declarator(
            &node.declarators[0].node,
            &node.declarators[0].span
        );
    }

    fn visit_init_declarator(
        &mut self,
        node: &'a parse_ast::InitDeclarator,
        _span: &'a Span
    ) {
        let var_name = self.visit_declarator(&node.declarator.node, &node.declarator.span);
        if let Some(ref initializer) = node.initializer {
            match initializer.node {
                parse_ast::Initializer::Expression(ref e) => {
                    let expr_id = self.visit_expression(&e.node, &e.span);
                    let node_id = self.current_max_id;
                    self.current_max_id = self.current_max_id + 1;
                    // let relation = AstRelation::Assign {
                    //     id: node_id,
                    //     var_name: var_name.clone(),
                    //                             expr_id,
                    // };
                    // self.tree.add_node(node_id, relation);
                    // self.tree.link_child(node_id, type_id);
                    // self.tree.link_child(node_id, expr_id);
                    // return node_id;
                }
                _ => panic!("Feature not implemented"),
            }
        } else {
            panic!("Feature not implemented")
        }
    }

    fn visit_while_statement(
        &mut self,
        node: &'a parse_ast::WhileStatement,
        _span: &'a Span,
    )  {
        let cond_id = self.visit_expression(&node.expression.node, &node.expression.span);
        let body_id = self.visit_statement(&node.statement.node, &node.statement.span);
        let node_id = self.current_max_id;
        self.current_max_id = self.current_max_id + 1;
        // let relation = AstRelation::While {
        //     id: node_id,
        //     cond_id,
        //     body_id,
        // };
        // self.tree.add_node(node_id, relation);
        // self.tree.link_child(node_id, cond_id);
        // self.tree.link_child(node_id, body_id);
        // // return node_id;
    }

    fn visit_if_statement(&mut self, node: &'a parse_ast::IfStatement, _span: &'a Span) {
        let cond_id = self.visit_expression(&node.condition.node, &node.condition.span);
        let then_id = self.visit_statement(&node.then_statement.node, &node.then_statement.span);
        if let Some(ref e) = node.else_statement {
            let else_id = self.visit_statement(&e.node, &e.span);
            let node_id = self.current_max_id;
            self.current_max_id = self.current_max_id + 1;
            // let relation = AstRelation::IfElse {
            //     id: node_id,
            //     cond_id,
            //     then_id,
            //     else_id,
            // };
            // self.tree.add_node(node_id, relation);
            // self.tree.link_child(node_id, cond_id);
            // self.tree.link_child(node_id, then_id);
            // self.tree.link_child(node_id, else_id);
            // // return node_id;
        } else {
            let node_id = self.current_max_id;
            self.current_max_id = self.current_max_id + 1;
            // let relation = AstRelation::If {
            //     id: node_id,
            //     cond_id,
            //     then_id,
            // };
            // self.tree.add_node(node_id, relation);
            // self.tree.link_child(node_id, cond_id);
            // self.tree.link_child(node_id, then_id);
                // // return node_id;
        }
    }

    fn visit_expression(&mut self, node: &'a parse_ast::Expression, _span: &'a Span) {
        match *node {
            parse_ast::Expression::Identifier(ref i) => {
                let var_name = i.node.name.clone();
                let node_id = self.current_max_id;
                self.current_max_id = self.current_max_id + 1;
                // let relation = AstRelation::Var {
                //     id: node_id,
                //     var_name: var_name.clone(),
                // };
                // self.tree.add_node(node_id, relation);
                // // return node_id;
            }
            parse_ast::Expression::Constant(ref c) => return self.visit_constant(&c.node, &c.span),
            parse_ast::Expression::Call(ref c) => {
                self.visit_call_expression(&c.node, &c.span)
            }
            parse_ast::Expression::BinaryOperator(ref b) => {
                self.visit_binary_operator_expression(&b.node, &b.span)
            }
            parse_ast::Expression::Statement(ref s) => self.visit_statement(&s.node, &s.span),
            _ => panic!("Feature not implemented"),
        }
    }

    fn visit_call_expression(
        &mut self,
        node: &'a parse_ast::CallExpression,
        _span: &'a Span,
    ) {
        let fun_name;
        match node.callee.node {
            parse_ast::Expression::Identifier(ref i) => fun_name = i.node.name.clone(),
            _ => panic!("Expected a function identifier"),
        }

        // self.current_function.push_str(&fun_name);
        let mut arg_ids = vec![];
        for argument in &node.arguments {
            arg_ids.push(self.visit_expression(&argument.node, &argument.span))
        }
        let node_id = self.current_max_id;
        self.current_max_id = self.current_max_id + 1;
        // let relation = AstRelation::FunCall {
        //     id: node_id,
        //     fun_name: fun_name.clone(),
        //     arg_ids: arg_ids.clone(),
        // };
        // self.tree.add_node(node_id, relation);
        // self.tree.replace_children(node_id, arg_ids);
        // // return node_id;
    }

    fn visit_binary_operator_expression(
        &mut self,
        node: &'a parse_ast::BinaryOperatorExpression,
        _span: &'a Span,
    ) {
        let arg1_id = self.visit_expression(&node.lhs.node, &node.lhs.span);
        let arg2_id = self.visit_expression(&node.rhs.node, &node.rhs.span);
        let node_id = self.current_max_id;
        self.current_max_id = self.current_max_id + 1;

        return;
        match node.operator.node {
            parse_ast::BinaryOperator::Plus => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::Minus => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::Multiply => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::Divide => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::Greater => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::GreaterOrEqual => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::Less => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::LessOrEqual => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::Equals => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::LogicalAnd => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::LogicalOr => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            parse_ast::BinaryOperator::Assign => {
                // let relation = AstRelation::BinaryOp {
                //     id: node_id,
                //     arg1_id,
                //     arg2_id,
                // };
                // self.tree.add_node(node_id, relation);
                // self.tree.link_child(node_id, arg1_id);
                // self.tree.link_child(node_id, arg2_id);
                // // return node_id;
            }
            _ => panic!("Feature not implemented"),
        }
    }

    fn visit_constant(&mut self, node: &'a parse_ast::Constant, _span: &'a Span) {
        let node_id = self.current_max_id;
        self.current_max_id = self.current_max_id + 1;
        match *node {
            parse_ast::Constant::Integer(_) => {
                // let relation = AstRelation::Int { id: node_id };
                // self.tree.add_node(node_id, relation);
                // return node_id;
            }
            parse_ast::Constant::Float(_) => {
                // let relation = AstRelation::Float { id: node_id };
                // self.tree.add_node(node_id, relation);
                // return node_id;
            }
            parse_ast::Constant::Character(_) => {
                // let relation = AstRelation::Char { id: node_id };
                // self.tree.add_node(node_id, relation);
                // return node_id;
            }
        }
    }

    // Put together function definition node.
    fn visit_declarator_for_function(
        &mut self,
        node: &'a parse_ast::Declarator,
        _span: &'a Span
    ) {
        let fun_name = self.visit_declarator_kind(&node.kind.node, &node.kind.span);

        self.current_function.function_name.push_str(&fun_name);
        // let mut arg_ids = vec![];
        for derived in &node.derived {
            self.visit_derived_declarator(&derived.node, &derived.span);
        }
        let node_id = self.current_max_id;
        self.current_max_id = self.current_max_id + 1;
        // let relation = AstRelation::FunDef {
        //     id: node_id,
        //     fun_name: fun_name.clone(),
        //     arg_ids: arg_ids.clone()
        // };
        // self.tree.add_node(node_id, relation);
        // self.tree.replace_children(node_id, arg_ids);
        // self.tree.link_child(node_id, return_type_id);
        // self.tree.link_child(node_id, body_id);
        // // return node_id;
    }

    // Get function name.
    fn visit_declarator_kind(
        &mut self,
        node: &'a parse_ast::DeclaratorKind,
        _span: &'a Span,
    ) -> String {
        match *node {
            parse_ast::DeclaratorKind::Identifier(ref i) => return i.node.name.clone(),
            _ => panic!("Feature not implemented"),
        }
        
    }

    fn visit_kr_identifier(
        &mut self,
        node: &'a parse_ast::Identifier,
        _span: &'a Span,
    )
    {
        println!("visit_kr_identifier {:#?}", *node);
    }

    // Traverse to function declarator (for now, will need this for other declarators later too).
    fn visit_derived_declarator(
        &mut self,
        node: &'a parse_ast::DerivedDeclarator,
        _span: &'a Span,
    ) {
        match *node {
            parse_ast::DerivedDeclarator::Function(ref f) => {
                self.visit_function_declarator(&f.node, &f.span)
            }
            parse_ast::DerivedDeclarator::KRFunction(ref f) => {

                println!("{}", f.len());
                for identifier in f {
                    self.visit_kr_identifier(&identifier.node, &identifier.span);
                }
            }
            parse_ast::DerivedDeclarator::Pointer(ref f) => {
                self.current_function.return_type.push_str("*"); // push_str("*");
                // println!("*");
            }
            _ => println!("visit_derived_declarator skipping {:#?}", *node),
        }
    }

    fn visit_function_declarator(
        &mut self,
        node: &'a parse_ast::FunctionDeclarator,
        _span: &'a Span,
    )  {
        let mut arg_ids = vec![];
        for arg in &node.parameters {
            arg_ids.push(self.visit_parameter_declaration(&arg.node, &arg.span));
        }

        self.function_declarations.push(self.current_function.clone());
        self.current_function = MyFunc::default();
        // self.current_function = "".to_string();
    }

    fn visit_parameter_declaration(
        &mut self,
        node: &'a parse_ast::ParameterDeclaration,
        _span: &'a Span,
    )  {
        let mut type_id = 0;
        for specifier in &node.specifiers {
            self.visit_declaration_specifier(&specifier.node, &specifier.span);
        }
        let var_name;
        if let Some(ref declarator) = node.declarator {
            var_name = self.visit_declarator(&declarator.node, &declarator.span);
        } else {
            var_name = String::from("");
        }

        // let arg = MyArg {name:var_name, typename:"unk".to_string()};

        if( self.current_function.args.len() > 0)
        {
            self.current_function.args.last_mut().unwrap().name = var_name.clone();
        }
        else {
            println!("should have had args.len {:#?}", *node);
        }


        // self.current_function.push_str(&var_name);
        let node_id = self.current_max_id;
        self.current_max_id = self.current_max_id + 1;
        // let relation = AstRelation::Arg {
        //     id: node_id,
        //     var_name: var_name.clone()
        // };
        // self.tree.add_node(node_id, relation);
        // self.tree.link_child(node_id, type_id);
        // // return node_id;
    }

    // Separate method for argument declarator since we only need the variable name from here.
    fn visit_declarator(&mut self, node: &'a parse_ast::Declarator, _span: &'a Span) -> String {
        for n in &node.derived
        {
            match n.node {
                parse_ast::DerivedDeclarator::Pointer(ref f) => {
                    // self.current_function.args.last_mut().unwrap().name

                    if( self.current_function.args.len() > 0)
                    {
                        self.current_function.args.last_mut().unwrap().pointers.push_str("*");
                    }
                    else {
                        let arg = MyArg {
                            name:"unk".to_string(), 
                            typename:"unk_type".to_string(),
                            pointers:"*".to_string()
                        };
                        self.current_function.args.push(arg);
                        // println!("visit_declarator:derived should have had args.len {:#?}", n);
                    }
            
                    // self.current_function.args.push_str("*");
                }
                _ => println!("visit_declarator:derived skipping {:#?}", n),
            }
        }

        println!("visit_declarator {:#?}", node.derived);
        return self.visit_declarator_kind(&node.kind.node, &node.kind.span);
    }
}

// #[cfg(test)]
// mod tests {
//     use crate::parser_interface;

//     // Run with "cargo test print_for_debug -- --show-output".
//     #[test]
//     fn print_for_debug() {
//         parser_interface::parse_with_lang_c(&String::from("./tests/dev_examples/c/example2.c"))
//             .pretty_print();
//     }
// }





// #[test]
// fn test_empty() {
//     let mut config = Config::default();
//     let parsed = parse_with_lang_c(&"symbols/test/empty.c".to_string());
// }

// #[test]
// fn test_pointer_args() {
//     let mut config = Config::default();
//     let parsed = parse_with_lang_c(&"symbols/test/pointer_args.c".to_string());
// }

// ok next steps is parse the map file and get the addresses?

// use std::collections::HashMap;

// fn parse_map() {
//     let input = r#"
//         0x000000000601ac00                SetStageOverlayAddress
//         0x0000000006030400                pad_06030400
//         0x0000000006030af8                pad_06030af8
//         0x00000000060505e0                zero_TEXT_END = .
//         0x000000000004c560                zero_TEXT_SIZE = ABSOLUTE ((zero_TEXT_END - zero_TEXT_START))
//         0x000000000004c560                __romPos = (__romPos + SIZEOF (.zero))
//         0x000000000004c560                __romPos = ALIGN (__romPos, 0x10)
//         0x000000000004c560                zero_ROM_END = __romPos
//         0x00000000060505e0                zero_VRAM_END = .
//         /DISCARD/
//         *(*)
//         0x0000000006066040                _func_06066040 = 0x6066040
//         0x00000000060661bc                _func_060661BC = 0x60661bc
//         0x0000000006066330                _func_06066330 = 0x6066330
//         0x0000000006066400                _func_06066400 = 0x6066400
//     "#;

//     let mut address_mapping: HashMap<u64, String> = HashMap::new();

//     for line in input.lines() {
//         let parts: Vec<&str> = line.trim().split_whitespace().collect();
//         if parts.len() >= 2 {
//             if let Ok(address) = u64::from_str_radix(parts[0].trim_start_matches("0x"), 16) {
//                 let value = parts[1].to_string();
//                 address_mapping.insert(address, value);
//             }
//         }
//     }

//     // Print the HashMap contents
//     for (key, value) in &address_mapping {
//         println!("key {:x} value {}", key, value);
//     }
// }

use std::collections::HashMap;
use std::fs::File;
use std::io::{BufRead, BufReader};

fn parse_file(filename: &str) -> HashMap<String, u64> {
    let file = File::open(filename).expect("Failed to open file");
    let reader = BufReader::new(file);

    let mut address_mapping: HashMap<String, u64> = HashMap::new();

    for line in reader.lines() {
        if let Ok(line) = line {
            let parts: Vec<&str> = line.trim().split_whitespace().collect();
            if parts.len() >= 2 {
                if let Ok(address) = u64::from_str_radix(parts[0].trim_start_matches("0x"), 16) {
                    let value = parts[1].to_string();
                    address_mapping.insert(value, address);
                }
            }
        }
    }

    address_mapping
}

// fn main() {

// }

// #[test]
// fn test_parse_map() {
//     // parse_map();

//     let filename = "/build/saturn/zero.map";
//     let address_mapping = parse_file(filename);

//     // Print the HashMap contents
//     for (key, value) in &address_mapping {
//         println!("key {:x} value {}", key, value);
//     }
// }


use serde::{Serialize, Deserialize};
use serde_json;

#[derive(Serialize, Deserialize, Default, Clone)]
struct Argument {
    #[serde(rename = "type")]
    type_: String,
    name: String,
}

#[derive(Serialize, Deserialize, Default, Clone)]
struct Details {
    rettype: String,
    callconv: String,
    name: String,
    arguments: Vec<Argument>,
    noreturn: bool,
    vararg: bool,
}

#[derive(Serialize, Deserialize, Default, Clone)]
struct Function {
    address: u64,
    name: String,
    funcdef: String,
    details: Details,
}

#[derive(Serialize, Deserialize)]
struct FunctionData {
    functions: Vec<Function>,
}

#[test]
fn test_json() {
    // Define the function data
    let functions = vec![
        Function {
            address: 4506160,
            name: "FatalError".to_string(),
            funcdef: "void C2_HOOK_CDECL FatalError(int pStr_index, ...)".to_string(),
            details: Details {
                rettype: "void".to_string(),
                callconv: "cdecl".to_string(),
                name: "FatalError".to_string(),
                arguments: vec![
                    Argument {
                        type_: "int".to_string(),
                        name: "pStr_index".to_string(),
                    },
                ],
                noreturn: false,
                vararg: true,
            },
        },
        Function {
            address: 4507008,
            name: "OpenDiagnostics".to_string(),
            funcdef: "void C2_HOOK_FASTCALL OpenDiagnostics(void)".to_string(),
            details: Details {
                rettype: "void".to_string(),
                callconv: "fastcall".to_string(),
                name: "OpenDiagnostics".to_string(),
                arguments: vec![],
                noreturn: false,
                vararg: false,
            },
        },
        Function {
            address: 4507024,
            name: "dr_dprintf".to_string(),
            funcdef: "void C2_HOOK_CDECL dr_dprintf(const char* fmt_string, ...)".to_string(),
            details: Details {
                rettype: "void".to_string(),
                callconv: "cdecl".to_string(),
                name: "dr_dprintf".to_string(),
                arguments: vec![
                    Argument {
                        type_: "const char*".to_string(),
                        name: "fmt_string".to_string(),
                    },
                ],
                noreturn: false,
                vararg: true,
            },
        },
    ];

    // Create the function data struct
    let function_data = FunctionData { functions };

    // Serialize the function data to JSON
    let json = serde_json::to_string_pretty(&function_data).unwrap();

    // Print the JSON
    println!("{}", json);
}

    // use std::fs::File;
use std::io::prelude::*;


fn do_file(c_filename: String, map_filename: String, functions : & mut Vec<Function> ) {
  
    let mut config = Config::default();
    // config.cpp_options.push("-Xpreprocessor".to_string());
    // config.cpp_options.push("-D".to_string());
    // config.cpp_options.push("PERMUTER".to_string());

    // println!("cpp_options {:?}", config.cpp_options);
    // exit(0);
    // let parsed = parse(&config, "example.c");
    let parsed = parse_with_lang_c(&c_filename);

    // parse map

    let address_mapping = parse_file(&map_filename);

    // // Print the HashMap contents
    // for (key, value) in &address_mapping {
    //     println!("key {:x} value {}", key, value);
    // }    


    // let mut functions : Vec<Function> = Vec::new();


    // #[derive(Clone, Debug, Default)]
    // struct MyArg
    // {
    //     typename: String,
    //     name: String,
    //     pointers: String
    // }
    
    // #[derive(Clone, Debug, Default)]
    // pub struct MyFunc
    // {
    //     return_type: String,
    //     function_name: String,
    //     args: Vec<MyArg>
    // }
    
    for parse in parsed {

        let mut function = Function::default();

        // function.address = address_mapping.get(parse.function_name);

        if let Some(address) = address_mapping.get(&parse.function_name).cloned() {
            // Value is present, assign it to function.address
            function.address = address;
            function.name = parse.function_name.clone();
            // println!("Address: {}", address);
            println!("{} : {}", parse.function_name, address);
        } else {
            // Value is not present
            // println!("Function not found {}", parse.function_name);

            let mangled = format!("_{}", parse.function_name);

            // try appending _
            if let Some(address) = address_mapping.get(&mangled).cloned() {
                // Value is present, assign it to function.address
                function.address = address;
                function.name = mangled.clone();
                println!("{} : {}", mangled, address);
            } else {
                // Value is not present
                println!("Function not found {}", parse.function_name);
            }
        }

        let mut funcdef = format!("{} {}(", parse.return_type, function.name);

        for (index, arg) in parse.args.iter().enumerate()
        {

            let _arg = Argument {
                type_: format!("{} {}", arg.typename, arg.pointers),
                name: arg.name.clone(),
            };


            if arg.typename != "void"
            {
                function.details.arguments.push(_arg);
            }

            if index == parse.args.len() - 1
            {
                funcdef = format!("{} {} {} {}", funcdef, arg.typename, arg.pointers, arg.name);

            }
            else {
                funcdef = format!("{} {} {} {},", funcdef, arg.typename, arg.pointers, arg.name);

            }
        }


        funcdef = format!("{})", funcdef);

        function.funcdef = funcdef.clone();


        function.details.rettype = parse.return_type;
        function.details.callconv = "cdecl".to_string();
        function.details.name = function.name.clone();



        functions.push(function.clone());



        // function.name 
    
        // struct AstBuilder {
        //     // tree: Tree,
        //     current_max_id: u64,
        //     function_declarations: Vec<MyFunc>,
        //     // current_function: String
        //     current_function: MyFunc
        // }



    }
}

// use std::collections::HashMap;
use std::env;

#[derive(Debug, Clone)]
struct OverlayConfig {
    c_file_path: String,
    map_file_path: String,
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let mut overlays: Vec<OverlayConfig> = Vec::new();
    let mut symbols_out_path: Option<String> = None;

    let mut i = 1;
    while i < args.len() {
        match args[i].as_str() {
            "--overlay" => {
                let c_file_path = args[i + 1].clone();
                let map_file_path = args[i + 2].clone();
                overlays.push(OverlayConfig {
                    c_file_path,
                    map_file_path,
                });
                i += 3;
            }
            "--symbols_out_path" => {
                symbols_out_path = Some(args[i + 1].clone());
                i += 2;
            }
            _ => {
                println!("Invalid argument: {}", args[i]);
                return;
            }
        }
    }

    let mut functions : Vec<Function> = Vec::new();


    for overlay in overlays.clone()
    {
        do_file(overlay.c_file_path,overlay.map_file_path, & mut functions);
    }

    // Access the parsed values
    println!("Overlays: {:?}", overlays.clone());
    if let Some(path) = symbols_out_path {

        // Create the function data struct
        let function_data = FunctionData { functions };

        // Serialize the function data to JSON
        let json = serde_json::to_string_pretty(&function_data).unwrap();

        // Print the JSON
        println!("{}", json);
        println!("Symbols Output Path: {:?}", path);

        // Create the file
        let mut file = File::create(path.clone()).expect("Failed to create the file");

        // Write the JSON contents to the file
        file.write_all(json.as_bytes()).expect("Failed to write to the file");

        println!("JSON data written to {}", path.clone());



    } else {
        println!("No symbols output path specified.");
    }


}
