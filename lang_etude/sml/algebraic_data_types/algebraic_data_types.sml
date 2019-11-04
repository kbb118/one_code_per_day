
datatype week = Sunday | Monday | Tuesday | Wednesday | Thursday | Friday | Saturday
datatype person = MkPerson of string * int

datatype stone = Black | White
datatype cell = Empty | Full of stone

datatype third = Mentos

val board = [
    [Empty, Empty, Empty, Empty],
    [Empty, Full Black, Full White, Empty],
    [Empty, Full White, Full Black, Empty],
    [Empty, Empty, Empty, Empty]]

(*
(* this causes a compile error because third is not a candidate for Full.*)
val bad_board = [
    [Empty, Empty, Empty, Empty],
    [Empty, Full Black, Full White, Empty],
    [Empty, Full White, Full Black, Empty],
    [Empty, Empty, Empty, Full Mentos]
*)

(* 代数的データ型は再帰的に定義できる *)
(* ファイルシステムの要素を代数的データ型entryで表す *)
datatype entry = File of string | Directory of string * entry list

val fs = Directory (".", [
                        Directory ("src", [File "main.rs", File "lib.rs"]),
                        File "README.md",
                        Directory ("targed", [Directory ("debug", [])])
                    ])

fun isWeekend w = case w of
                       Saturday => true
                    |  Sunday   => true
                    |  other    => false
