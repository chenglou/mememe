module Inner = {
  type config = {
    height: int,
    width: int,
    top: int,
    left: int,
    key: string,
    component: ReasonReact.reactElement,
  };

  type changeSpec = int;
  [@bs.deriving abstract]
  type props = {
    configs: list(config),
    pat: list(config) => changeSpec,
  };

  let make = props => {
    let configs = props->configs;
    let pat = props->pat;
    let (state, setState) = ReactHooks.useState(configs);
    let components = Belt.List.map(configs, ({component}) => component);
    Js.log("fuck");
    <> {ReasonReact.array(components->Belt.List.toArray)} </>;
  };
};

open Yoga;
let root = node->create;
root->setWidth(500);
root->setHeight(300);
root->setJustifyContent(justifyCenter);

let child1 = node->create;
/* child1->setFlex(Js.Math.floor(Js.Math.random() *. 3.) + 1); */
child1->setFlex(1);
child1->setAlignContent(alignStretch);
child1->setAlignItems(alignStretch);
/* child1->setFlexDirection(
     Js.Math.random() < 0.5 ? flexDirectionRow : flexDirectionColumn,
   ); */

let child2 = node->create;
/* child2->setFlex(Js.Math.floor(Js.Math.random() *. 3.) + 1); */
child2->setFlex(2);
child2->setAlignContent(alignStretch);
child2->setAlignItems(alignStretch);
/* child2->setFlexDirection(
     Js.Math.random() < 0.5 ? flexDirectionRow : flexDirectionColumn,
   ); */

root->insertChild(child1, ~index=0, ());
root->insertChild(child2, ~index=1, ());

root->calculateLayout(500, 300, directionLTR);

let rootLayout = root->getComputedLayout;
let child1Layout = child1->getComputedLayout;
let child2Layout = child2->getComputedLayout;

/* TODO: don't forget to freeRecursive */

let randomColor = () => {
  let rand = Js.Math.random;
  let s = 255.;
  let r = Js.Math.round(rand() *. s);
  let g = Js.Math.round(rand() *. s);
  let b = Js.Math.round(rand() *. s);
  {j|rgb($r, $g, $b)|j};
};

let draw = (layout, elem) => {
  let color = randomColor();
  let s =
    ReactDOMRe.Style.make(
      ~top=string_of_int(layout##top) ++ "px",
      ~left=string_of_int(layout##left) ++ "px",
      ~height=string_of_int(layout##height) ++ "px",
      ~width=string_of_int(layout##width) ++ "px",
      ~position="absolute",
      ~border={j|5px solid $color|j},
      ~boxSizing="border-box",
      ~opacity="0.5",
      (),
    );
  <div style=s> elem </div>;
};

let make = () => {
  /* <>
       /* {draw(rootLayout, ReasonReact.null)} */
       {draw(child1Layout, ReasonReact.string("1"))}
       {draw(child2Layout, ReasonReact.string("2"))}
     </>; */
  let pat = _ => 1;
  ReactHooks.createElement(Inner.make, Inner.props(~configs=[], ~pat));
};
