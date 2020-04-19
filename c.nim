{.compile: "a.c".}

type
  S* = ptr object
    val*: cint
    sz*: cint
    arr*: UncheckedArray[byte] # it is important to have byte here to align struct

  SS_CONTAINER {.bycopy.} = object
    sz: cint
    arr: UncheckedArray[byte] # it is important to have byte here to align struct

  SS_UNION {.union, bycopy.} = object
    val: cint
    r: SS
    container: SS_CONTAINER

  SS* {.bycopy.} = ptr object
    t*: cint
    u*: SS_UNION

proc mkS(): S {.
  importc: "mkS", header: "\"a.h\"".}

proc printS(s: S) {.
  importc: "printS", header: "\"a.h\"".}

proc pS(s: S) =
  echo "S: val: " , s.val, " sz: ", s.sz

proc `[]`(s: S, i: int): S =
  cast[UncheckedArray[S]](s.arr)[i]

proc mkSS(): SS {.
  importc: "mkSS", header: "\"a.h\"".}

proc printAllSS(ss: SS) {.
  importc: "printAllSS", header: "\"a.h\"".}

proc printSS(ss: SS) {.
  importc: "printSS", header: "\"a.h\"".}

proc `[]`(ss: SS, i: int): SS =
  cast[UncheckedArray[SS]](ss.u.container.arr)[i]

proc main() =
  let s = mkS()
  printS(s)
  pS(s)
  pS(s[0])
  pS(s[1])
  let ss = mkSS()
  echo "C:"
  printAllSS(ss)

  echo()
  echo "NIM:"
  printSS(ss)
  let r = ss.u.r
  printSS(r)
  printSS(r[0])
  printSS(r[1])


when isMainModule:
  main()
