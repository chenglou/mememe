type justify;
[@bs.module "yoga-layout/dist/entry-browser"]
external justifyCenter: justify = "JUSTIFY_CENTER";
[@bs.module "yoga-layout/dist/entry-browser"]
external alignStretch: justify = "ALIGN_STRETCH";
[@bs.module "yoga-layout/dist/entry-browser"]
external flexDirectionRow: justify = "FLEX_DIRECTION_ROW";
[@bs.module "yoga-layout/dist/entry-browser"]
external flexDirectionColumn: justify = "FLEX_DIRECTION_COLUMN";

type direction;
[@bs.module "yoga-layout/dist/entry-browser"]
external directionLTR: direction = "DIRECTION_LTR";

type node;
[@bs.send] external setWidth: (node, int) => unit = "";
[@bs.send] external setHeight: (node, int) => unit = "";
[@bs.send] external calculateLayout: (node, int, int, direction) => unit = "";
[@bs.send] external setJustifyContent: (node, justify) => unit = "";
[@bs.send] external setFlex: (node, int) => unit = "";
[@bs.send] external setAlignContent: (node, justify) => unit = "";
[@bs.send] external setAlignItems: (node, justify) => unit = "";
[@bs.send] external setFlexDirection: (node, justify) => unit = "";
[@bs.send]
external insertChild: (node, node, ~index: int=?, unit) => unit = "";
type result = {
  .
  "left": int,
  "right": int,
  "top": int,
  "bottom": int,
  "height": int,
  "width": int,
};
[@bs.send] external getComputedLayout: node => result = "";

type nodeClass;
[@bs.module "yoga-layout/dist/entry-browser"]
external node: nodeClass = "Node";
[@bs.send] external create: nodeClass => node = "";
