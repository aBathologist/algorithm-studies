(* Implement an algorithm to determine if a string has all unique characters.
   What if you * can not use additional data structures? *)

module CharSet = Set.Make (Char)

let unique_chars : String.t -> bool = fun str ->
  let chars = String.to_seq str in
  let n_uniques = CharSet.of_seq chars |> CharSet.cardinal in
  let n_chars = Seq.fold_left (fun prev _ -> prev + 1) 0 chars in
  n_uniques = n_chars


(* 1 2 3 4 5
 *     ^   ^
 *  start = 2
 * *)
let quicksort_bytes str =
  let rec quicksort' str start len =
    if len > 1 then
      let pivot = Bytes.get str (len / 2)
      and i = ref start
      and j = ref (len - 1)
      in
      while i < j do
        while Bytes.get str !i < pivot do incr i done;
        while Bytes.get str !j > pivot do decr j done;

        if i < j then
          let i_val = Bytes.get str !i in
          Bytes.set str !i (Bytes.get str !j);
          Bytes.set str !j i_val;

          incr i;
          decr j;
      done;
      quicksort' str 0 !i;
      quicksort' str !i (len - !i)
  in
  quicksort' str 0 (Bytes.length str)


let unique_chars' : Bytes.t -> bool = fun str ->
  let all_unique str =
    let len = Bytes.length str in
    if len < 2 then
      true
    else
      let i = ref 1
      and c = ref (Bytes.get str 0)
      in

      while !i < Bytes.length str && Bytes.get str !i <> !c do
        c := Bytes.get str !i;
      done;

      !i = len
  in
  quicksort_bytes str;
  all_unique str
