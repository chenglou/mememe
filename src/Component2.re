let randomColor = () => {
  let rand = Js.Math.random;
  let s = 255.;
  let r = Js.Math.round(rand() *. s);
  let g = Js.Math.round(rand() *. s);
  let b = Js.Math.round(rand() *. s);
  {j|rgb($r, $g, $b)|j};
};

module Inner = {
  type config = {
    height: int,
    width: int,
    top: int,
    left: int,
    key: string,
    component: ReasonReact.reactElement,
  };

  let draw = config => {
    let color = randomColor();
    let s =
      ReactDOMRe.Style.make(
        ~top=string_of_int(config.top) ++ "px",
        ~left=string_of_int(config.left) ++ "px",
        ~height=string_of_int(config.height) ++ "px",
        ~width=string_of_int(config.width) ++ "px",
        ~position="absolute",
        ~border={j|5px solid $color|j},
        ~boxSizing="border-box",
        ~opacity="0.5",
        ~transition="all 1.5s",
        (),
      );
    <div key={config.key} style=s> {config.component} </div>;
  };

  type configs =
    | One(config)
    | Two(config, config);

  type changeSpec = string;

  [@bs.deriving abstract]
  type props = {
    configs,
    pat: (configs, configs) => changeSpecWhatIsTheSpec,
  };

  let make = props => {
    let configs = props->configsGet;
    let pat = props->pat;
    /* let (state, setState) = ReactHooks.useState(configs); */
    let components =
      switch (configs) {
      | One(config) => [|draw(config)|]
      | Two(config1, config2) =>
        [|config1, config2|]
        ->Belt.SortArray.stableSortBy((a, b) => String.compare(a.key, b.key))
        ->Belt.Array.map(draw)
      };
    <> {ReasonReact.array(components)} </>;
  };
};

/* ======================================================== third-party ======================================================== */
/* ======================================================== third-party ======================================================== */
/* ======================================================== third-party ======================================================== */
/* ======================================================== third-party ======================================================== */

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

let make = () => {
  /* <>
       /* {draw(rootLayout, ReasonReact.null)} */
       {draw(child1Layout, ReasonReact.string("1"))}
       {draw(child2Layout, ReasonReact.string("2"))}
     </>; */
  let (toggle, setState) = ReactHooks.useState(0);
  ReactHooks.useEffect(() => {
    let id = Js.Global.setTimeout(() => setState(toggle + 1), 2000);
    Some(() => Js.Global.clearTimeout(id));
  });

  let toggled = toggle mod 2 == 0;

  let config1 =
    Inner.{
      height: toggled ? 100 : 200,
      width: 200,
      top: toggled ? 220 : 120,
      left: 100,
      key: "first",
      component: {
        ReasonReact.string("heyhey 1");
      },
    };
  let config2 =
    Inner.{
      height: 100,
      width: 200,
      top: toggled ? 110 : 10,
      left: 100,
      key: "second",
      component: {
        ReasonReact.string("bye 2");
      },
    };
  let configs = toggled ? Inner.Two(config1, config2) : One(config1);

  let pat = (before, after) => {
    switch (before, after) {
    | (Inner.One(config), Inner.Two(config1, config2)) => "some spec"
    | (Two(config1, config2), One(config)) => "some other spec"
    | _ => "some whatever"
    };
  };

  ReactHooks.createElement(Inner.make, Inner.props(~configs, ~pat));
};
