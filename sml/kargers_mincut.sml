(* Loading utility modules — repo here: https://github.com/aBathologist/sml-utils *)
CM.autoload "../../sml/utils/sources.cm";


(* Abbreviating oft used module *)
structure L = ListPlus
structure O = Option


(* Naive implementation of Karger's minimum cut *)
structure NaiveKargers =
struct

  type node = string
  type edge = node * node

  type graph = node list * edge list

  structure Rand = RandC.List (type item = edge)

  fun make edges =
    let
        fun edgeNodes [] = []
          | edgeNodes ((x,y)::es) = x::y::(edgeNodes es)
        val nodes = (L.nub o edgeNodes) edges
    in
        (nodes, edges)
    end

  fun contract (graph as (nodes, edges)) (edge as (x,y)) =
    let
        val xy = x ^ "-" ^ y

        fun replace (a,b) =
          case (a = x orelse a = y, b = x orelse b = y)
           of (true,  true)  => NONE
           |  (true,  false) => SOME (xy, b)
           |  (false, true)  => SOME (a, xy)
           |  (false, false) => SOME (a,b)

        val edges' = (L.map O.valOf o L.filter O.isSome o L.map replace) edges
        val nodes' = xy :: (L.exclude (Fn.equal x) o L.exclude (Fn.equal y)) nodes
    in
        (nodes', edges')
    end

  fun minCut (graph as (nodes, edges)) =
    case nodes
     of ([_] | []) => 0
      | [a,b]      => L.length edges
      | _          => (minCut o contract graph o Rand.member) edges

end


(* Loading the test files into edge lists *)
structure GraphFile =
struct

  fun load file =
    let
        val emptyLines = Fn.equal ""
        val lines      = (L.exclude emptyLines o File.Read.lines) file
        val tokens     = String.tokens (Fn.equal #" ")
        val nodeList   = L.map tokens lines
        val nodes      = L.map L.hd nodeList
    in
        L.map (Pair.product (hd, tl)) nodeList
    end

  fun edgePairs file =
    let
        val adjacencyPairs  = load file
        fun pairSort (a, b) = if String.< (a, b) then (a, b) else (b, a)
        fun adjacencyListPairs (n, ns) = L.map (pairSort o Pair.wrap n) ns
    in
        (L.nub o L.concat o L.map adjacencyListPairs) adjacencyPairs
    end

end


(* testing out the implementation of the algorithm *)

structure NK = NaiveKargers

fun testCutOnFile file shouldBe =
  let
      val graph         = (NK.make o GraphFile.edgePairs) file
      val minCuts       = L.tabulate (100, fn _ => NK.minCut graph)
      fun listMinInt ls = L.foldl (Int.min) (L.hd ls) ls
  in
      shouldBe = listMinInt minCuts
  end

val file4Cuts = "../../nlang-algorithms/karger_minimum_cut/four_cut_graphs/a_4.txt"
val file1Cuts = "../../nlang-algorithms/karger_minimum_cut/one_cut_graphs/a_1.txt"
val file3Cuts = "../../nlang-algorithms/karger_minimum_cut/three_cut_graphs/a_3.txt"

(* Running three test cases on three files   | The results of the test cases *)

val test1cuts = testCutOnFile file1Cuts 1 (* | val test1cuts = true : bool *)
val test3cuts = testCutOnFile file3Cuts 3 (* | val test3cuts = true : bool *)
val test4cuts = testCutOnFile file4Cuts 4 (* | val test4cuts = true : bool *)
