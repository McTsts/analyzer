(** {{!RelationAnalysis} Relational integer value analysis} using {!Elina} domains ([elina]). *)

open Analyses

include RelationAnalysis

let spec_module: (module MCPSpec) Lazy.t =
  lazy (
    let module RelImpl = (val ApronDomain.get_implementation "elina") in
    if Messages.tracing then Messages.trace "test" "ea1";
    let module Man = (val ApronDomain.get_manager (module RelImpl)) in
    if Messages.tracing then Messages.trace "test" "ea2";
    let module AD = ApronDomain.D2 (Man) in
    if Messages.tracing then Messages.trace "test" "ea3";
    let diff_box = GobConfig.get_bool "ana.apron.invariant.diff-box" in
    if Messages.tracing then Messages.trace "test" "ea4";
    let module AD = (val if diff_box then (module ApronDomain.BoxProd (AD): RelationDomain.RD) else (module AD)) in
    if Messages.tracing then Messages.trace "test" "ea5";
    let module Priv = (val RelationPriv.get_priv ()) in
    if Messages.tracing then Messages.trace "test" "ea6";
    let module Spec =
    struct
      include SpecFunctor (Priv) (AD) (ApronPrecCompareUtil.Util)
      let name () = "elina"
    end
    in
    if Messages.tracing then Messages.trace "test" "ea7";
    (module Spec)
  )

let get_spec (): (module MCPSpec) =
  if Messages.tracing then Messages.trace "test" "eal1";
  let ret = Lazy.force spec_module in
  if Messages.tracing then Messages.trace "test" "eal2";
  ret

let after_config () =
  if Messages.tracing then Messages.trace "test" "ac1";
  let module Spec = (val get_spec ()) in
  MCP.register_analysis (module Spec : MCPSpec);
  let ret = GobConfig.set_string "ana.path_sens[+]"  (Spec.name ()) in 
  if Messages.tracing then Messages.trace "test" "ac2";
  ret

let _ =
  let ret = AfterConfig.register after_config in 
  ret


let () =
  Printexc.register_printer
    (function
      | Apron.Manager.Error e ->
        let () = Apron.Manager.print_exclog Format.str_formatter e in
        Some(Printf.sprintf "Apron.Manager.Error\n %s" (Format.flush_str_formatter ()))
      | _ -> None (* for other exceptions *)
    )
