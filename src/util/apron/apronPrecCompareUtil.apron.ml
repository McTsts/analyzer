(** {!ApronDomain} precision comparison. *)

open PrecCompareUtil
open ApronDomain
open RelationalImplementation
open ApronImplementation

(* Currently serialization of Apron results only works for octagons. *)
module OctagonD = ApronDomain.OctagonD
module Util =
  functor (D2: RelationDomain.S2) ->
  struct
    include Util (RelationPrecCompareUtil.MyNode) (D2)
    type marshal = D2.marshal RH.t
    type dump = marshal dump_gen
    type result = Dom.t RH.t result_gen

    let init () =
      let module ApronImpl : Implementation = ApronImplementation in
      let module OctagonManagerInstance = OctagonManager (ApronImpl) in 
      Apron.Manager.set_deserialize OctagonManagerInstance.mgr

    let unmarshal (m: marshal): D2.t RH.t =
      RH.map (fun _ -> D2.unmarshal) m
  end

include Util(OctagonD)
