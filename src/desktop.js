self.importScripts('./yoga.js')
const Node = yoga.Node;

var count = 13

function addRandomChildren(node, depth) {
  if (depth > count) {
    return null;
  }

  const child1 = Node.create();
  child1.setFlex(Math.floor(Math.random() * 3) + 1);
  child1.setAlignContent(yoga.ALIGN_STRETCH);
  child1.setAlignItems(yoga.ALIGN_STRETCH);
  child1.setFlexDirection(Math.random() < 0.5 ? yoga.FLEX_DIRECTION_ROW : yoga.FLEX_DIRECTION_COLUMN)

  const child2 = Node.create();
  child2.setFlex(Math.floor(Math.random() * 3) + 1);
  child2.setAlignContent(yoga.ALIGN_STRETCH);
  child2.setAlignItems(yoga.ALIGN_STRETCH);
  child1.setFlexDirection(Math.random() < 0.5 ? yoga.FLEX_DIRECTION_ROW : yoga.FLEX_DIRECTION_COLUMN)

  node.insertChild(child1);
  node.insertChild(child2);

  return {
    l: addRandomChildren(child1, depth + 1),
    lNode: child1,
    r: addRandomChildren(child2, depth + 1),
    rNode: child2,
  }
}

function computeAllChildren(depth, tree) {
  if (depth > count) {
    return null;
  }

  return {
    l: computeAllChildren(depth + 1, tree.l),
    lValue: tree.lNode.getComputedLayout(),
    r: computeAllChildren(depth + 1, tree.r),
    rValue: tree.rNode.getComputedLayout(),
  }
}

// self.addEventListener('message', function(e) {

//   var someResult
//   for (var i = 0; i < 20000; i++) {
//     const Node = yoga.Node;
//     const root = Node.create();
//     root.setWidth(500);
//     root.setHeight(300);
//     root.setJustifyContent(yoga.JUSTIFY_CENTER);

//     const node1 = Node.create();
//     node1.setWidth(100);
//     node1.setHeight(100);

//     const node2 = Node.create();
//     node2.setWidth(100);
//     node2.setHeight(100);

//     root.insertChild(node1, 0);
//     root.insertChild(node2, 1);

//     root.calculateLayout(500, 300, yoga.DIRECTION_LTR);

//     var l1 = root.getComputedLayout();
//     var l2 = node1.getComputedLayout();
//     var l3 = node2.getComputedLayout();

//     someResult = [l1, l2, l3].toString();
//     root.freeRecursive();
//   }


//   self.postMessage(someResult);

// }, false);

self.addEventListener('message', function (e) {

  const root = Node.create();
  root.setWidth(500);
  root.setHeight(300);
  root.setAlignContent(yoga.ALIGN_STRETCH);
  root.setAlignItems(yoga.ALIGN_STRETCH);

  var layoutTree = addRandomChildren(root, 0)
  root.calculateLayout(500, 300, yoga.DIRECTION_LTR);
  var layoutTree = computeAllChildren(0, layoutTree)

  self.postMessage(layoutTree)

  root.freeRecursive();

}, false);

