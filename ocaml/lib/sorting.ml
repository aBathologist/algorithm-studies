module Functional = struct
  module Mergesort = struct
    let merge compare xs ys =
      let rec merge' xs ys = match xs, ys with
        | [], ys -> ys
        | xs, [] -> xs
        | ((x::xs) as xs'), ((y::ys) as ys') ->
          let comp = compare x y in
          if comp < 1  then
            x :: merge' xs ys'
          else
            y :: merge' xs' ys
      in
      merge' xs ys

    let top_down ~compare list =
      let rec split = function
        | [x] -> ([x], [])
        | []  -> ([] , [])
        | (x::y::rest) ->
          let xs, ys = split rest in
          (x::xs, y::ys)
      in
      let rec mergesort xs = match xs with
        | [] | [_] -> xs
        | xs ->
          let xs, ys = split xs in
          merge compare (mergesort xs) (mergesort ys)
      in
      mergesort list

    let bottom_up ~compare list =
      let rec merge_pairs = function
        | s1 :: s2 :: sorteds -> merge compare s1 s2 :: merge_pairs sorteds
        | sorteds -> sorteds
      in
      let rec merge_all = function
        | [sorted] -> sorted
        | sorteds  -> merge_all (merge_pairs sorteds)
      in
      merge_all (List.map (fun x -> [x]) list)
  end
end

module Imperative = struct
  module Mergesort = struct

    let get_incr r = let v = !r in incr r; v

    let merge xs ys =
      let res = Array.make (Array.length xs + Array.length ys) 0 in
      let xi = ref 0 and yi = ref 0 and resi = ref 0 in
      while !xi < Array.length xs || !yi < Array.length ys do
        let resv =
          if !xi >= Array.length xs then
            ys.(get_incr(yi))
          else if !yi >= Array.length ys then
            xs.(get_incr(xi))
          else if compare xs.(!xi) ys.(!yi) <= 0 then
            xs.(get_incr(xi))
          else
            ys.(get_incr(yi))
        in
        Array.set res (!resi) resv;
        incr resi;
      done;
      res

    let split arr =
      let i = (Array.length arr / 2) in
      (Array.sub arr 0 i,
       Array.sub arr i (Array.length arr - i))

    let rec mergesort arr =
      if Array.length arr < 2 then
        arr
      else
        let (a, b) = split arr in
        merge (mergesort a) (mergesort b)
  end

  module Slice = CCArray_slice

  let quicksort : int Array.t -> unit = fun arr ->
    let rec quicksort' : int Slice.t -> unit = fun slice ->
      let len = Slice.length slice in

      if len > 1 then begin
        let pivot = Slice.get slice (len / 2)
        and i = ref 0
        and j = ref (len - 1)
        in
        while !i < !j do
          while Slice.get slice !i < pivot do incr i done;
          while Slice.get slice !j > pivot do decr j done;

          if !i < !j then begin
            let i_val = Slice.get slice !i in
            Slice.set slice !i (Slice.get slice !j);
            Slice.set slice !j i_val;

            incr i;
            decr j;
          end
        done;

        quicksort' (Slice.sub slice 0 !i);
        quicksort' (Slice.sub slice !i (len - !i));
      end
    in
    (* Take the array into an aliased array slice *)
    Slice.full arr |> quicksort'
end
