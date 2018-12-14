/**
 * Copyright 2004-present Facebook. All Rights Reserved.
 *
 * @emails oncall+reason
 */;

[@bs.module "React"]
external useState: 'state => ('state, 'state => unit) = "";

[@bs.module "React"]
external useReducer:
  (('state, 'action) => 'state, 'state) => ('state, 'action => unit) =
  "";

[@bs.module "React"]
external useEffect: (unit => option(unit => unit)) => unit = "useEffect";
[@bs.module "React"]
external useEffect0:
  (unit => option(unit => unit), [@bs.as {json|[]|json}] _) => unit =
  "useEffect";
[@bs.module "React"]
external useEffect1: (unit => option(unit => unit), array('a)) => unit =
  "useEffect";
[@bs.module "React"]
external useEffect2: (unit => option(unit => unit), ('a, 'b)) => unit =
  "useEffect";

[@bs.module "React"]
external useLayoutEffect: (unit => option(unit => unit)) => unit =
  "useLayoutEffect";
[@bs.module "React"]
external useLayoutEffect0:
  (unit => option(unit => unit), [@bs.as {json|[]|json}] _) => unit =
  "useLayoutEffect";
[@bs.module "React"]
external useLayoutEffect1: (unit => option(unit => unit), array('a)) => unit =
  "useLayoutEffect";
[@bs.module "React"]
external useLayoutEffect2: (unit => option(unit => unit), ('a, 'b)) => unit =
  "useLayoutEffect";

[@bs.module "React"] external useMemo: (unit => 'any) => 'any = "useMemo";
[@bs.module "React"]
external useMemo0: (unit => 'any, [@bs.as {json|[]|json}] _) => 'any =
  "useMemo";
[@bs.module "React"]
external useMemo1: (unit => 'any, array('a)) => 'any = "useMemo";
[@bs.module "React"]
external useMemo2: (unit => 'any, ('a, 'b)) => 'any = "useMemo";

type ref('value) = {. [@bs.set] "current": 'value};
type domRef = Js.nullable(Dom.element) => unit;

[@bs.module "React"] external useRef: 'value => ref('value) = "";

[@bs.module "React"]
external createElement:
  ('props => ReasonReact.reactElement, 'props) => ReasonReact.reactElement =
  "";

[@bs.module "React"] external createRef: unit => ref('value) = "";

[@bs.module "React"]
external forwardRef:
  (('props, ref(Js.nullable(Dom.element))) => ReasonReact.reactElement) =>
  (. 'props) => ReasonReact.reactElement =
  "";

/* typically JSX would generate this call. we proably need one for keys too */
[@bs.set]
external wrapRef: ('props, ref(Js.nullable(Dom.element))) => unit = "ref";

/* These are both hacky internop things because React has n different ways of dealing with refs */
external refForDom: ref(Js.nullable(Dom.element)) => domRef = "%identity";

external refForHooks: domRef => ref(Js.nullable(Dom.element)) = "%identity";
