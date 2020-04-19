{.link: "a.o".}

type
  S* = ptr object
    val*: cint
    sz*: cint
    arr*: UncheckedArray[S]

  SS_CONTAINER = object
    sz: cint
    arr: UncheckedArray[SS]

  SS_UNION {.union.} = object
    val: cint
    r: SS
    container: SS_CONTAINER

  SS* = ptr object
    t*: cint
    u*: SS_UNION

proc mkS(): S {.
  importc: "mkS", header: "\"a.h\"".}

proc printS(s: S) {.
  importc: "printS", header: "\"a.h\"".}

proc pS(s: S) =
  echo "S: val: " , s.val, " sz: ", s.sz

proc `[]`(s: S, i: int): S =
  s.arr[i]

proc mkSS(): SS {.
  importc: "mkSS", header: "\"a.h\"".}

proc printSS(ss: SS) {.
  importc: "printSS", header: "\"a.h\"".}

proc `[]`(ss: SS, i: int): SS =
  ss.u.container.arr[i]

proc main() =
  # let s = mkS()
  # printS(s)
  # pS(s)
  # pS(s[0])
  # pS(s[1])
  let ss = mkSS()
  printSS(ss)
  let r = ss.u.r
  printSS(r)
  # printSS(r[0])
  # printSS(r[1])


when isMainModule:
  main()
