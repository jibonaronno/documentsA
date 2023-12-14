// import Konva from "konva";
import Konva from "../local-packages/konva";
import store from "@/store/page"
import sensorSymbols from '../static/shape/Symbols.json';

import Vue from 'vue';
import { data } from "jquery";

export const EventBus = new Vue();


Konva.Node.prototype.getTextNode = function() {
  return this._textNode;
};

Konva.Node.prototype.setTextNode = function(textNode) {
  this._textNode = textNode;
};

//selected Nodes set using _addTrNodes
let selectedNodes = []

/* COMMAND CLASS */

class AddObjCommand {
  constructor(objArr) {
    this._objArr = objArr;
  }

  execute() {}

  undo() {
    this._objArr.forEach((element) => {
      element.destroy();
    });

    return "empty";
  }
}

class DeleteObjCommand {
  constructor(objArr) {
    //this._objArr = objArr
    this.prevAttrs = [];

    objArr.forEach((element) => {
      this.prevAttrs.push({
        className: element.className,
        attrs: element.attrs,
      });
    });
    EventBus.$emit('onDeleteNode', objArr[0]);
  }

  execute() {}

  undo() {
    let objTmp = [];
    this.prevAttrs.forEach((el) => {
      let kObj;

      if (el.className === "Rect") {
        kObj = new Konva.Rect(el.attrs);
      } else if (el.className === "Ellipse") {
        kObj = new Konva.Ellipse(el.attrs);
      } else if (el.className === "Path") {
        kObj = new Konva.Path(el.attrs);
      } else if (el.className === "Line") {
        kObj = new Konva.Line(el.attrs);
      } else if (el.className === "Text") {
        kObj = new Konva.Text(el.attrs);
      }

      objTmp.push(kObj);
    });

    return { isRestore: true, objects: objTmp };
  }
}

class PasteCommand {
  constructor(sourceObjArr, destObjArr) {
    this._objArr = destObjArr;
    this.prevObjArr = sourceObjArr;
  }

  execute() {}

  undo() {
    this._objArr.forEach((element) => {
      element.destroy();
    });

    return this.prevObjArr;
  }
}

class MoveCommand {
  constructor(objArr) {
    this._objArr = objArr;
    this.prevPosition = [];
  }

  execute() {
    this._objArr.forEach((el) => {
      this.prevPosition.push({ x: el.attrs.prevX, y: el.attrs.prevY });
    });
  }

  undo() {
    for (let i = 0; i < this._objArr.length; i++) {
      const el = this._objArr[i];
      const p = this.prevPosition[i];
      el.x(p.x);
      el.y(p.y);
    }

    return this._objArr;
  }
}

class SizeCommand {
  constructor(objArr) {
    this._objArr = objArr;
    this.prevSize = [];
  }

  execute() {
    this._objArr.forEach((el) => {
      let attr = {
        scaleX: el.attrs.prevScaleX,
        scaleY: el.attrs.prevScaleY,
        x: el.attrs.prevX,
        y: el.attrs.prevY,
        width: el.attrs.prevW,
        height: el.attrs.prevH,
      };

      if (el.className === "Ellipse") {
        attr.width = el.attrs.radiusX;
        attr.height = el.attrs.radiusY;
      }

      this.prevSize.push(attr);
    });
  }

  undo() {
    for (let i = 0; i < this._objArr.length; i++) {
      const el = this._objArr[i];
      const s = this.prevSize[i];

      el.x(s.x);
      el.y(s.y);
      el.scaleX(s.scaleX);
      el.scaleY(s.scaleY);

      if (el.className === "Ellipse") {
        el.radiusX(s.width);
        el.radiusY(s.height);
      } else {
        el.width(s.width);
        el.height(s.height);
      }
    }
  }
}

class SetAttrHeightCommand {
  constructor(objArr, value, incDec) {
    this._objArr = objArr;
    this._value = value;
    this.prevSize = [];
    this._incDec = incDec;
  }

  execute() {
    let rtn;

    this._objArr.forEach((el) => {
      const className = el.className;
      if (className === "Rect" || className === "Image") {
        this.prevSize.push({
          height: el.attrs.height,
          scaleY: el.attrs.scaleY,
        });

        if (this._incDec === undefined) {
          el.height(this._value);
        } else {
          el.height(
            el.getClientRect({ skipStroke: true }).height + this._value
          );
        }

        el.scaleY(1);
      } else if (className === "Ellipse") {
        this.prevSize.push({ height: el.getHeight(), scaleY: el.attrs.scaleY });

        if (this._incDec === undefined) {
          el.height(this._value);
        } else {
          el.height(
            el.getClientRect({ skipStroke: true }).height + this._value
          );
        }

        el.scaleY(1);
      } else if (className === "Line") {
        this.prevSize.push({ width: el.attrs.points[2], scaleX: 1 });

        if (el.attrs.name.split("_")[0] === "lineH") return;

        if (this._incDec === undefined) {
          el.attrs.points[2] = this._value;
        } else {
          el.attrs.points[2] += this._value;
        }

        el.draw();
        rtn = "forceUpdate";
      } else if (className === "Path") {
        this.prevSize.push({ scaleY: el.attrs.scaleY });

        if (this._incDec === undefined) {
          el.scaleY(this._value / el.attrs.height);
        } else {
          el.scaleY(
            (el.getClientRect({ skipStroke: true }).height + this._value) /
              el.attrs.height
          );
        }
      } else if (className === "Text") {
        this.prevSize.push({
          height: el.attrs.height,
          scaleY: el.attrs.scaleY,
        });
        //el.height( this._value / el.attrs.scaleY )
        if (this._incDec === undefined) {
          el.scaleY(1);
          el.height(this._value / el.attrs.scaleY);
        } else {
          el.height(
            el.getClientRect({ skipStroke: true }).height + this._value
          );
        }
      }
    });

    return rtn;
  }

  undo() {
    let rtn;

    for (let i = 0; i < this._objArr.length; i++) {
      const el = this._objArr[i];
      const s = this.prevSize[i];

      const className = el.className;
      if (className === "Rect" || className === "Image") {
        el.scaleY(s.scaleY);
        el.height(s.height);
      } else if (className === "Ellipse") {
        el.scaleY(s.scaleY);
        el.setHeight(s.height);
      } else if (className === "Line") {
        el.attrs.points[2] = s.width;
        el.draw();
        rtn = "forceUpdate";
      } else if (className === "Path") {
        el.scaleY(s.scaleY);
      } else if (className === "Text") {
        el.scaleY(s.scaleY);
        el.height(s.height);
      }
    }

    return rtn;
  }
}

class SetAttrWidthCommand {
  constructor(objArr, value, incDec) {
    this._objArr = objArr;
    this._value = value;
    this.prevSize = [];
    this._incDec = incDec;
  }

  execute() {
    let rtn;

    this._objArr.forEach((el) => {
      const className = el.className;

      if (className === "Rect" || className === "Image") {
        this.prevSize.push({ width: el.attrs.width, scaleX: el.attrs.scaleX });

        if (this._incDec === undefined) {
          el.width(this._value);
        } else {
          el.width(el.getClientRect({ skipStroke: true }).width + this._value);
        }

        el.scaleX(1);
      } else if (className === "Ellipse") {
        this.prevSize.push({ width: el.getWidth(), scaleX: el.attrs.scaleX });

        if (this._incDec === undefined) {
          el.width(this._value);
        } else {
          el.width(el.getClientRect({ skipStroke: true }).width + this._value);
        }

        el.scaleX(1);
      } else if (className === "Line") {
        this.prevSize.push({ width: el.attrs.points[2], scaleX: 1 });

        //if( el.attrs.name.split('_')[0] === 'lineV' ) return

        if (this._incDec === undefined) {
          el.attrs.points[2] = this._value;
        } else {
          el.attrs.points[2] += this._value;
        }

        el.draw();
        rtn = "forceUpdate";
      } else if (className === "Path") {
        this.prevSize.push({ scaleX: el.attrs.scaleX });

        if (this._incDec === undefined) {
          el.scaleX(this._value / el.attrs.width);
        } else {
          el.scaleX(
            (el.getClientRect({ skipStroke: true }).width + this._value) /
              el.attrs.width
          );
        }
      } else if (className === "Text") {
        this.prevSize.push({ width: el.attrs.width, scaleX: el.attrs.scaleX });
        //el.width( this._value / el.attrs.scaleX )
        if (this._incDec === undefined) {
          el.scaleX(1);
          el.width(this._value / el.attrs.scaleX);
        } else {
          el.width(el.getClientRect({ skipStroke: true }).width + this._value);
        }
      }
    });

    return rtn;
  }

  undo() {
    let rtn;

    for (let i = 0; i < this._objArr.length; i++) {
      const el = this._objArr[i];
      const s = this.prevSize[i];
      const className = el.className;

      if (className === "Rect" || className === "Image") {
        el.scaleX(s.scaleX);
        el.width(s.width);
      } else if (className === "Ellipse") {
        el.scaleX(s.scaleX);
        el.setWidth(s.width);
      } else if (className === "Line") {
        el.attrs.points[2] = s.width;
        el.draw();
        rtn = "forceUpdate";
      } else if (className === "Path") {
        el.scaleX(s.scaleX);
      } else if (className === "Text") {
        el.scaleX(s.scaleX);
        el.width(s.width);
      }
    }

    return rtn;
  }
}

class SetAttrCommand {
  constructor(objArr, attr, value) {
    this._objArr = objArr;
    this._attr = attr;
    this._value = value;
    this.oldValue = [];
  }

  execute() {
    this._objArr.forEach((el) => {
      //this.oldValue = el[this._attr]()
      this.oldValue.push(el[this._attr]());
      el[this._attr](this._value);
    });
  }

  undo() {
    this._objArr.forEach((el) => {
      el[this._attr](this.oldValue.shift());
    });
  }
}

class SetOpacityCommand {
  constructor(objArr, attr, value) {
    this._objArr = objArr;
    this._attr = attr;
    this._value = value;
    this.oldValue = [];
  }

  execute() {
    this._objArr.forEach((el) => {
      let fVal = el[this._attr]();
      console.log(fVal);
      this.oldValue.push(fVal);

      let rgb = Konva.Util.colorToRGBA(fVal);
      console.log(rgb);

      el[this._attr](
        "rgba(" + rgb.r + "," + rgb.g + "," + rgb.b + "," + this._value + ")"
      );
    });
  }

  undo() {
    this._objArr.forEach((el) => {
      el[this._attr](this.oldValue.shift());
    });
  }
}

class SetBrOpacityCommand {
  constructor(objArr, attr, value) {
    this._objArr = objArr;
    this._attr = attr;
    this._value = value;
    this.oldValue = [];
  }

  execute() {
    let rtn;
    this._objArr.forEach((el) => {
      let fVal = el.attrs[this._attr];
      console.log(fVal);
      this.oldValue.push(fVal);

      let rgb = Konva.Util.colorToRGBA(fVal);
      console.log(rgb);

      el.attrs[this._attr] =
        "rgba(" + rgb.r + "," + rgb.g + "," + rgb.b + "," + this._value + ")";
      el.draw();
      rtn = "forceUpdate";
    });

    return rtn;
  }

  undo() {
    let rtn;
    this._objArr.forEach((el) => {
      el.attrs[this._attr] = this.oldValue.shift();
      el.draw();
      rtn = "forceUpdate";
    });

    return rtn;
  }
}

class SetBrAttrCommand {
  constructor(objArr, attr, value) {
    this._objArr = objArr;
    this._attr = attr;
    this._value = value;
    this.oldValue = null;
  }

  execute() {
    let rtn;
    this._objArr.forEach((el) => {
      this.oldValue = el.attrs[this._attr];
      el.attrs[this._attr] = this._value;
      el.draw();
      console.log("oldVal : " + this.oldValue + " newVal : " + this._value);
      rtn = "forceUpdate";
    });

    return rtn;
  }

  undo() {
    let rtn;
    this._objArr.forEach((el) => {
      el.attrs[this._attr] = this.oldValue;
      el.draw();
      rtn = "forceUpdate";
    });

    return rtn;
  }
}

class LayeringCommand {
  constructor(objArr, attr) {
    this._objArr = objArr;
    this._attr = attr;
    this._prevIndex = [];
  }

  execute() {
    this._objArr.forEach((el) => {
      this._prevIndex.push(el.index);

      if (this._attr === "top") {
        el.moveToTop();
      } else if (this._attr === "up") {
        el.moveUp();
      } else if (this._attr === "down") {
        el.moveDown();
      } else if (this._attr === "bottom") {
        el.moveToBottom();
      }
    });
  }

  undo() {
    for (let i = 0; i < this._objArr.length; i++) {
      const el = this._objArr[i];
      const index = this._prevIndex[i];
      el.setZIndex(index);
    }
  }
}

class SortingCommand {
  constructor(objArr, attr, metaKeySortFlag) {
    this._objArr = objArr;
    this._attr = attr;
    this._prevPos = [];
    this._metaKeySortFlag = metaKeySortFlag;
  }

  execute() {
    console.log("execute sorting / flag : " + this._metaKeySortFlag);
    let stPos;

    if (this._attr === "left") {
      const mapX = this._objArr.map((o) => o.attrs.x);

      if (this._metaKeySortFlag) {
        stPos = this._objArr[0].attrs.x;
      } else {
        stPos = Math.min(...mapX);
      }

      this._prevPos = mapX;

      this._objArr.forEach((el) => {
        el.x(stPos);
      });
    } else if (this._attr === "center") {
      const mapX = this._objArr.map((o) => o.attrs.x);

      if (this._metaKeySortFlag) {
        stPos =
          this._objArr[0].attrs.x +
          this._objArr[0].getClientRect({ skipStroke: true }).width / 2;
      } else {
        const maxX = this._objArr.map(
          (o) => o.attrs.x + o.getClientRect({ skipStroke: true }).width
        );
        //this._objArr.forEach(el =>{
        //    console.log('('+el.attrs.x +','+el.getClientRect({skipStroke: true}).width+')')
        //})

        console.log(mapX);

        stPos = (Math.max(...maxX) - Math.min(...mapX)) / 2;
        stPos = parseInt(stPos + Math.min(...mapX));
        // console.log('stPos : '+ stPos)
      }

      this._prevPos = mapX;
      this._objArr.forEach((el) => {
        //console.log('('+stPos+','+Math.floor((el.getClientRect({skipStroke: true}).width / 2)) +','+parseInt(stPos - Math.floor((el.getClientRect({skipStroke: true}).width / 2)))+')')
        el.x(
          parseInt(
            stPos - Math.floor(el.getClientRect({ skipStroke: true }).width / 2)
          )
        );
      });
    } else if (this._attr === "right") {
      const mapX = this._objArr.map(
        (o) => o.attrs.x
        //o => o.attrs.x + (o.className === 'Line'? o.getClientRect({ skipTransform: true, skipStroke: true}).width : o.getClientRect({skipStroke: true}).width)
      );

      if (this._metaKeySortFlag) {
        stPos =
          this._objArr[0].attrs.x +
          this._objArr[0].getClientRect({ skipStroke: true }).width;
      } else {
        stPos = Math.max(...mapX);
      }
      console.log(mapX);
      this._prevPos = this._objArr.map((o) => o.attrs.x);

      this._objArr.forEach((el) => {
        //let value;
        //if (el.className === 'Line') {
        //  if (el.attrs.name.split('_')[0] === 'lineV') {
        //    console.log('Zero')
        //    value = 0;
        //  } else {
        //    value = el.getClientRect({ skipTransform: true, skipStroke: true}).width;
        //  }
        //} else {
        //  value = el.getClientRect({skipStroke: true}).width;
        //}
        //if (el.attrs.x === stPos)
        //{
        //    console.log('Olleh')
        //    value = 0
        //}
        //const newXPos = stPos - value;
        //console.log("stPos : "+stPos + " value : "+value + " newXPos : "+newXPos)
        //el.x(newXPos)
        el.x(stPos);
        //el.x( stPos - ( el.className === 'Line'? el.attrs.name.split('_')[0] === 'lineV' ? 0 :
        //    el.getClientRect({ skipTransform: true, skipStroke: true}).width
        //    : el.getClientRect({skipStroke: true}).width)  )
      });
    } else if (this._attr === "top") {
      const mapY = this._objArr.map((o) => o.attrs.y);

      if (this._metaKeySortFlag) {
        console.log("_metaKeySortFlag >>>");
        stPos = this._objArr[0].attrs.y;
      } else {
        stPos = Math.min(...mapY);
      }

      this._prevPos = mapY;

      this._objArr.forEach((el) => {
        el.y(stPos);
      });
    } else if (this._attr === "middle") {
      const mapY = this._objArr.map((o) => o.attrs.y);
      this._prevPos = mapY;

      if (this._metaKeySortFlag) {
        let cR = this._objArr[0].getClientRect({ skipStroke: true });
        stPos = parseInt(cR.y + cR.height / 2);

        this._objArr.forEach((el) => {
          el.y(stPos - el.getClientRect({ skipStroke: true }).height / 2);
        });
      } else {
        const maxY = this._objArr.map(
          (o) => o.attrs.y + o.getClientRect({ skipStroke: true }).height
        );

        stPos = (Math.max(...maxY) - Math.min(...mapY)) / 2;
        stPos = parseInt(stPos + Math.min(...mapY));

        this._objArr.forEach((el) => {
          el.y(stPos - el.getClientRect({ skipStroke: true }).height / 2);
        });
      }
    } else if (this._attr === "bottom") {
      const mapY = this._objArr.map(
        (o) => o.attrs.y + o.getClientRect({ skipStroke: true }).height
      );
      this._prevPos = this._objArr.map((o) => o.attrs.y);

      if (this._metaKeySortFlag) {
        let cR = this._objArr[0].getClientRect({ skipStroke: true });
        stPos = parseInt(cR.y + cR.height);
      } else {
        stPos = Math.max(...mapY);
      }

      this._objArr.forEach((el) => {
        el.y(stPos - el.getClientRect({ skipStroke: true }).height);
      });
    }
  }

  undo() {
    for (let i = 0; i < this._objArr.length; i++) {
      const el = this._objArr[i];
      const stPos = this._prevPos[i];

      if (this._attr === "left" || this._attr === "right") {
        el.x(stPos);
      } else if (this._attr === "center") {
        //el.x(stPos - (el.getClientRect({skipStroke: true}).width ))
        el.x(stPos);
      } else if (
        this._attr === "top" ||
        this._attr === "middle" ||
        this._attr === "bottom"
      ) {
        el.y(stPos);
      }
    }
  }
}

class PositionCommand {
  constructor(objArr, attr, value) {
    this._objArr = objArr;
    this._attr = attr.split(" ")[0];
    this._value = value;
    this.oldValue = null;
    this.action = attr.split(" ")[1];

    //console.log('PositionCommand')
  }

  execute() {
    this._objArr.forEach((el) => {
      this.oldValue = el[this._attr]();

      if (this.action === "up") {
        el[this._attr](this.oldValue + this._value);
      } else if (this.action === "down") {
        el[this._attr](this.oldValue - this._value);
      }
    });
  }

  undo() {
    this._objArr.forEach((el) => {
      if (this.action === "up") {
        this.oldValue = el[this._attr]();
        el[this._attr](this.oldValue - this._value);
      } else if (this.action === "down") {
        this.oldValue = el[this._attr]();
        el[this._attr](this.oldValue + this._value);
      }
    });
  }
}

class CommandHelper {
  constructor() {
    this.history = [];
  }

  executeCommand(command) {
    console.log("executeCommand");
    console.log(command);

    let rtn = command.execute();

    this.history.push(command);

    if (this.history.length > 30) {
      this.history.shift();
    }

    return rtn;
  }

  undo() {
    const command = this.history.pop();
    //console.log(command)
    if (command) {
      return command.undo();
    } else {
      return false;
    }
  }
}

export default class SSGB {
  constructor(containerId, options, parent) {
    if (options === undefined) {
      this.op = {
        width: 2560,
        height: 1115,
        drawColor: "#000000",
      };
    } else {
      this.op = options;
    }

    console.log("SSGB Init > ");
    console.log(this.op);

    this.parent = parent;
    this.selectedShape = null;
    this.prevShape = null;
    this.prevShapeGroup = null;
    this.tempCopyRepo = null;
    this.anchorTransform = false;
    this.useRelativePointerPosition = false;
    this.currAnchor = "none";
    this.currReady4CreateObj = "none";

    this.isLocatingSensor = false;
    this.sensorLocationInfo = {};

    this.GUIDELINE_OFFSET = 5;
    this.EVT_SLEEP_SECOND = 50;

    this.RelativePosConfig = {
      skipTransform: false,
      skipShadow: true,
      skipStroke: false,
      relativeTo: null,
    };

    this.stage = new Konva.Stage({
      container: containerId,
      width: this.op.width,
      height: this.op.height,
      name: "newDraw",
    });

    this.RelativePosConfig.relativeTo = this.stage;

    this.parent.drawName = "newDraw";
    this.parent.drawWidth = this.op.width;
    this.parent.drawHeight = this.op.height;
    this.parent.drawColor = this.op.drawColor;

    this.stage.on("mousedown", this._handleStageMouseDown.bind(this));
    this.stage.on("mouseup", this._handleStageMouseUp.bind(this));
    this.stage.on("dblclick", this._handleStageMouseDbClick.bind(this));

    EventBus.$on("onSaveImage", ()=>{
      this._saveSelectedNodesAsImage()
      }
    );

    //for setting bay name above bay from BayDialog.vue
    EventBus.$on("applyBayName", (bayName) => {
      console.log("Event received", bayName);
      var nodes = this.layer.getChildren(function (node) {
        const name = node.attrs.name;
        return !(name === "transformer" || name === "selectionRectangle" || name === "backgroundRect");
      });
    
      nodes.forEach((node) => {
        console.log(`@@@@@@@@@@hello node from applyBayName event$on${JSON.stringify(node)}`)
    
        if (node.attrs.bayName === bayName) {
          let textNode = node.getTextNode();
          console.log('@@@@@@@@@@@@this is the textNode from applyBayName event$on', textNode);
    
          if (!textNode) {
            textNode = new Konva.Text({
              text: bayName,
              fontSize: 20,
              fontFamily: 'Arial',
              fill: 'white',
              draggable: false,
              isBayName: true,
              linkedBayId: node.attrs.bayId,
            });
    
            node.setTextNode(textNode);
            this.layer.add(textNode);
          }
    
          // Function to update text node position
          const updateTextNodePosition = (textNode, bayNode) => {
            const bayNodeRect = bayNode.getClientRect();
            const centerX = bayNodeRect.x + bayNodeRect.width / 2;

            textNode.position({
              x: centerX - textNode.width() / 2,
              y: bayNodeRect.y - textNode.height(),
            });
          };
    
          updateTextNodePosition(textNode, node);
    
          node.on('dragmove', function () {
            updateTextNodePosition(textNode, this);
          });
        }
      });
    
      this.layer.draw();
    });
    

    EventBus.$on("applyMtrName", (mtrName) => {
      console.log("Event received", mtrName);
      var nodes = this.layer.getChildren(function (node) {
        const name = node.attrs.name;
        return !(name === "transformer" || name === "selectionRectangle" || name === "backgroundRect");
      });
    
      nodes.forEach((node) => {
        console.log(`@@@@@@@@@@hello node from applyMtrName event$on${JSON.stringify(node)}`)
    
        if (node.attrs.bayName === mtrName) {
          let textNode = node.getTextNode();
          let backgroundShape;
    
          if (!textNode) {
            // Create the text node
            textNode = new Konva.Text({
              text: mtrName,
              fontSize: 20,
              fontFamily: 'Arial',
              fill: 'white',
              draggable: false,
              resizeEnabled: false,
              linkedMTRId: node.attrs.bayId,
              isMTRName: true,
            });
    
            // Create the background shape (e.g., diamond)
            backgroundShape = new Konva.Path({
              data: "m 100 130 L 100 130 L 200 100 L 100 70 L 0 100 L 100 130"
              ,
              fill: '#0000FF',
              width: 200,
              height: 200,
              draggable: false,
              resizeEnabled: false,
              isMTRBackgroundShape: true,
              linkedMTRId: node.attrs.bayId,
            });
    
            // Add both nodes to the layer
            this.layer.add(backgroundShape);
            this.layer.add(textNode);
    
            // Store a reference to the text node in the MTR node
            node.setTextNode(textNode);
            // Optionally, store a reference to the background shape if needed
            node.setAttr('backgroundShape', backgroundShape);
          } else {
            // Retrieve the background shape if it already exists
            backgroundShape = node.getAttr('backgroundShape');
          }
    
          // Function to update text node and background shape position
          const updateNodePositions = (textNode, backgroundShape, mtrNode) => {
            const mtrNodeRect = mtrNode.getClientRect();
            const centerX = mtrNodeRect.x + mtrNodeRect.width / 2;
    
            // Update positions
            textNode.position({
              x: centerX - textNode.width() / 2,
              y: mtrNodeRect.y - textNode.height() - 30
            });
            backgroundShape.position({
              x: centerX - backgroundShape.width() / 2,
              y: mtrNodeRect.y - backgroundShape.height() + 60
            });
          };
    
          updateNodePositions(textNode, backgroundShape, node);
    
          node.on('dragmove', function () {
            updateNodePositions(textNode, backgroundShape, this);
          });
        }
      });
    
      this.layer.draw();
    });
    


    EventBus.$on("onLocatingSensor", (data)=>{
      this.isLocatingSensor = true;
      this.sensorLocationInfo = data;
    })
    EventBus.$on("reDrawBayMtr", (data)=>{
      console.log('re draw', data, 'node', JSON.parse(data.node.node));
      var nodes = this.layer.getChildren(function (node) {
        const name = node.attrs.name;
        if (name) {
          if (
            name !== "transformer" &&
            name !== "selectionRectangle" &&
            name !== "backgroundRect"
          ) {
            return node;
          }
        } else {
          return node;
        }
      });
      let bayNode = nodes.find(x=>{
        if(data.bayId){
          return x.attrs.bayId && x.attrs.bayId == data.bayId;
        }
        else if(data.mtrId){
          return x.attrs.bayId && x.attrs.bayId == data.mtrId;
        }
        
      });
  
      let newBayNodeAttr = JSON.parse(data.node.node);
      delete newBayNodeAttr.attrs.x;
      delete newBayNodeAttr.attrs.y;
      let currentBayX = bayNode.getAbsolutePosition();
      bayNode.attrs = newBayNodeAttr.attrs;
      bayNode.setAttr('x', currentBayX.x);
      bayNode.setAttr('y', currentBayX.y);

      nodes.forEach(x=>{
        if(x.attrs && x.attrs.isBayAttachment 
          && x.attrs.attachBayId == bayNode.attrs.bayId 
          && x.attrs.bayClass == bayNode.attrs.class)
        {
          x.destroy();
        }
      })
      let sensorList = data.sensorList;
      if(sensorList.length >0){
        for(let sensor of sensorList){
          let xCoorSensor = currentBayX.x + sensor.nodes.refX;
          let yCoorSensor = currentBayX.y + sensor.nodes.refY;
          let sensorConfig = JSON.parse(sensor.nodes.node);
          sensorConfig['x'] = xCoorSensor;
          sensorConfig['y'] = yCoorSensor;
          let kObj = new Konva.Path(sensorConfig);
          this._bindObjEvt(kObj);
          this.layer.add(kObj);
        }
      }
    })
    /*EventBus.$on('offLocatingSensor', (data)=>{
      this.isLocatingSensor = false;
    })*/

    var container = this.stage.container();

    // make it focusable
    container.tabIndex = 1;
    // focus it
    // also stage will be in focus on its click
    container.focus();
    container.addEventListener("keydown", this._containerKeydown.bind(this));

    /* Point map */
    this.PointList = [];

    /* Main Layer */
    this.layer = new Konva.Layer();
    console.log(this.layer.getCanvas());
    //this.layer.getCanvas().setPixelRatio(3)// = 3; // Optimize Rendering
    //console.log('window.devicePixelRatio : ' + window.devicePixelRatio)
    this.layer.getCanvas().setPixelRatio(window.devicePixelRatio);

    /* Tooltip Layer */
    this.tooltipLayer = new Konva.Layer();
    this.tooltip = new Konva.Text({
      text: "",
      fontFamily: "Arial",
      fontSize: 12,
      padding: 5,
      textFill: "black",
      fill: "black",
      alpha: 0.75,
      visible: false,
      brUse: true,
      brFill: "#ffffff",
    });

    this.commandHelper = new CommandHelper();

    this.background = new Konva.Rect({
      name: "backgroundRect",
      x: 0,
      y: 0,
      width: this.op.width,
      height: this.op.height,
      fill: this.op.drawColor,
      // remove background from hit graph for better perf
      // because we don't need any events on the background
      listening: false,
    });

    this.layer.add(this.background);

    /* LineGuide */
    this.layer.on(
      "dragmove",
      function (e) {
        if (this.transformer.nodes().length > 1) return; // limit node count

        // clear all previous lines on the screen
        this.layer.find(".guid-line").forEach((l) => l.destroy());

        // find possible snapping lines
        var lineGuideStops = this.getLineGuideStops(e.target);
        // find snapping points of current object
        var itemBounds = this.getObjectSnappingEdges(e.target);

        // now find where can we snap current object
        var guides = this.getGuides(lineGuideStops, itemBounds);

        // do nothing of no snapping
        if (!guides.length) {
          return;
        }

        this.drawGuides(guides);

        var absPos = e.target.absolutePosition();
        // now force object position
        guides.forEach((lg) => {
          switch (lg.snap) {
            case "start": {
              switch (lg.orientation) {
                case "V": {
                  absPos.x = lg.lineGuide + lg.offset;
                  break;
                }
                case "H": {
                  absPos.y = lg.lineGuide + lg.offset;
                  break;
                }
              }
              break;
            }
            case "center": {
              switch (lg.orientation) {
                case "V": {
                  absPos.x = lg.lineGuide + lg.offset;
                  break;
                }
                case "H": {
                  absPos.y = lg.lineGuide + lg.offset;
                  break;
                }
              }
              break;
            }
            case "end": {
              switch (lg.orientation) {
                case "V": {
                  absPos.x = lg.lineGuide + lg.offset;
                  break;
                }
                case "H": {
                  absPos.y = lg.lineGuide + lg.offset;
                  break;
                }
              }
              break;
            }
          }
        });
        e.target.absolutePosition(absPos);
      }.bind(this)
    );

    this.layer.on(
      "dragend",
      function (e) {
        // clear all previous lines on the screen
        this.layer.find(".guid-line").forEach((l) => l.destroy());
      }.bind(this)
    );

    this.transformer = new Konva.Transformer({
      name: "transformer",
      nodes: [],
      boundBoxFunc: (oldBox, newBox) => {
        const box = this._getClientRect(newBox);
        const isOut =
        box.x < 0 ||
        box.y < 0 ||
        box.x + box.width > this.stage.width() ||
        box.y + box.height > this.stage.height();
        
        // if new bounding box is out of visible viewport, let's just skip transforming
        // this logic can be improved by still allow some transforming if we have small available space
        if (isOut) {
          return oldBox;
        }
        return newBox;
      },
      ignoreStroke: true,
      metaKeySortFlag: false,
      anchorSize: 8,
      rotationSnaps: [
        0, 45, 90, 135, 180, 225, 270, 315
      ],
      
      rotateEnabled: true,

      //borderEnabled:true,
      //keepRatio: false
      padding: 0,
      // enabledAnchors: ['top-left', 'top-right', 'bottom-left', 'bottom-right']
    });

    /* Litmit Dragging & Resizeing */
    this.transformer.on("dragmove", () => {
      const boxes = this.transformer
        .nodes()
        .map((node) => node.getClientRect());
      const box = this.getTotalBox(boxes);

      this.transformer.nodes().forEach((shape) => {
        const absPos = shape.getAbsolutePosition();
        // where are shapes inside bounding box of all shapes?
        const offsetX = box.x - absPos.x;
        const offsetY = box.y - absPos.y;

        // we total box goes outside of viewport, we need to move absolute position of shape
        const newAbsPos = { ...absPos };
        if (box.x < 0) {
          newAbsPos.x = -offsetX;
        }
        if (box.y < 0) {
          newAbsPos.y = -offsetY;
        }

        /* not use this.stage.width() >>> use scaled size  */

        if (box.x + box.width > this.stage.width()) {
          newAbsPos.x = this.stage.width() - box.width - offsetX;
        }
        if (box.y + box.height > this.stage.height()) {
          newAbsPos.y = this.stage.height() - box.height - offsetY;
        }
        shape.setAbsolutePosition(newAbsPos);
      });
    });

    this.transformer.on(
      "dragend",
      function () {
        //console.log('transformer dragend >>>')

        /// Drag End Event Command record
        const objects = this.transformer.nodes();

        if (objects.length > 0) {
          // set MoveCommand record
          this.commandHelper.executeCommand(new MoveCommand(objects));

          // select one > property update
          if (objects.length === 1) {
            this._updatePropObj(objects[0]);
          }
        }
      }.bind(this)
    );

    /* Selection Setting */

    // add a new feature, lets add ability to draw selection rectangle
    this.selectionRectangle = new Konva.Rect({
      name: "selectionRectangle",
      fill: "rgb(185, 185, 185, 0.1)", //73 / b9
      stroke: "#737373",
      strokeWidth: 2,
      visible: false,
    });
    this.layer.add(this.selectionRectangle);

    // Mouse Event
    var x1, y1, x2, y2;

    this.relativePos = {
      x: 0,
      y: 0,
    };
    this.startMdEvt;

    this.stage.on(
      "mousedown touchstart",
      function (e) {
        console.log("@@mousedown touchstart");
        console.log(e);

        this.startMdEvt = e.evt;

        /// drag resize command record
        if (e.target.attrs.name && e.target.attrs.name.indexOf("anchor") > -1) {
          // is anchor
          this.anchorTransform = true;

          const objects = this.transformer.nodes();

          objects.forEach((el) => {
            el.attrs.prevScaleX = el.attrs.scaleX;
            el.attrs.prevScaleY = el.attrs.scaleY;
            el.attrs.prevX = el.attrs.x;
            el.attrs.prevY = el.attrs.y;
            el.attrs.prevW = el.attrs.width;
            el.attrs.prevH = el.attrs.height;
          });
        }

        // do nothing if we mousedown on any shape
        if (e.target !== this.stage) {
          return;
        }
        e.evt.preventDefault();

        if (this.useRelativePointerPosition) {
          x1 = this.stage.getRelativePointerPosition().x;
          y1 = this.stage.getRelativePointerPosition().y;
          x2 = this.stage.getRelativePointerPosition().x;
          y2 = this.stage.getRelativePointerPosition().y;
        } else {
          x1 = this.stage.getPointerPosition().x;
          y1 = this.stage.getPointerPosition().y;
          x2 = this.stage.getPointerPosition().x;
          y2 = this.stage.getPointerPosition().y;
        }

        this.selectionRectangle.visible(true);
        this.selectionRectangle.width(0);
        this.selectionRectangle.height(0);
      }.bind(this)
    );

    this.stage.on(
      "mousemove touchmove",
      function (e) {
        //console.log('@@mouseup touchmove')

        // do nothing if we didn't start selection
        if (!this.selectionRectangle.visible()) {
          return;
        }
        e.evt.preventDefault();

        if (this.useRelativePointerPosition) {
          x2 = this.stage.getRelativePointerPosition().x;
          y2 = this.stage.getRelativePointerPosition().y;
        } else {
          x2 = this.stage.getPointerPosition().x;
          y2 = this.stage.getPointerPosition().y;
        }

        this.selectionRectangle.setAttrs({
          x: Math.min(x1, x2),
          y: Math.min(y1, y2),
          width: Math.abs(x2 - x1),
          height: Math.abs(y2 - y1),
        });
      }.bind(this)
    );

    this.stage.on(
      "mouseup touchend",
      function (e) {
        const metaPressed = e.evt.shiftKey || e.evt.ctrlKey || e.evt.metaKey;
        
        if (this.anchorTransform) {
          this.anchorTransform = false;
          /// drag resize command record
          const objects = this.transformer.nodes();
          this.commandHelper.executeCommand(new SizeCommand(objects));

          // select one > property update
          if (objects.length === 1) {
            this._updatePropObj(objects[0]);
          }
        }

        // do nothing if we didn't start selection
        if (!this.selectionRectangle.visible()) {
          return;
        }
        e.evt.preventDefault();
        // update visibility in timeout, so we can check it in click event
        setTimeout(() => {
          this.selectionRectangle.visible(false);
        });

        //var shapes = this.stage.find('.rect');
        var shapes = this.layer.getChildren((node) => {
          if (node.isSelected) {
            return false;
          }

          const name = node.name();
          return (
            name !== "backgroundRect" &&
            name !== "selectionRectangle" &&
            name !== "transformer"
          );
        });

        var box, config;

        if (this.useRelativePointerPosition) {
          config = this.RelativePosConfig;
          box = this.selectionRectangle.getClientRect(config);
        } else {
          config = {};
          box = this.selectionRectangle.getClientRect();
        }

        var selected = shapes.filter((shape) =>
          this._haveIntersection(box, shape.getClientRect(config))
        );

        console.log("Konva.Util.haveIntersection : " + selected.length);
        console.log(selected);

        // update prop first item
        setTimeout(() => {
          this._updatePropObj(selected[0]);
        }, this.EVT_SLEEP_SECOND);

        // set flag property
        let action = "";

        if (selected.length > 1) {
          // Group Select
          console.log(" Group Select");

          this.parent.disablePropGroup = false;
          this.parent.disablePropObj = false;
          this.transformer.attrs.metaKeySortFlag = false;

          if (metaPressed) {
            action = "groupDragAppended";
          } else {
            action = "groupDrag";
          }
        } else if (selected.length === 1) {
          // Single Select
          console.log(" Single Select");
          this.parent.disablePropObj = false;
          this.parent.disablePropGroup = false;

          if (metaPressed) {
            action = "notAll";
          }

          if (!selected[0].isSelected) {
            selected[0].activeSelection(true);
          }
        } else {
          // no selected item maybe it was selected stage >>
          console.log("click tap Stage");
          this.parent.disablePropObj = true;
          this.prevShapeGroup = this.transformer.nodes();

          this.parent.ctxMenuClose();

          // inActive all obj
          // shapes
          //this.getNodeInfoList()
          if (!metaPressed) {
            shapes.forEach((element) => {
              if (element.isSelected) element.activeSelection(false);
            });
          } else {
            action = "notAll";
          }
        }

        if (metaPressed) {
          selected = this.transformer.nodes().concat(selected);
          selected.forEach((el) => {
            if (!el.isSelected) el.activeSelection(true);
          });
        }

        // EXCEPTION !!! Maximum Call Stack
        this._addTrNodes(selected, "mouseup touchend : drag select", action);
        container.focus();
      }.bind(this)
    );

    // clicks should select/deselect shapes
    this.stage.on(
      "click tap dragstart",
      function (e) {
        console.log("click tap", e);
        //console.log(e.target.getClientRect({ skipStroke: true}))
        //console.log(e.target.getClientRect({ skipTransform: true, skipStroke: true}))

        // if we are selecting with rect, do nothing
        if (this.selectionRectangle.visible()) {
          console.log("if we are selecting with rect, do nothing  << return");
          return;
        }

        /*
            if(e.target.getType() === 'Stage'){
                // text obj create after >> unselect
                this.selectionRectangle.x(-1)
                this.selectionRectangle.y(-1)
            }
            */

        // do we pressed shift or ctrl?

        const isSelected = this.transformer.nodes().indexOf(e.target) >= 0;
        const metaPressed = e.evt.shiftKey || e.evt.ctrlKey || e.evt.metaKey;

        // if(e.evt !=undefined){
          if ( !metaPressed && !isSelected) {
            // if no key pressed and the node is not selected
            // select just one
            if (
              e.target.parent !== this.transformer &&
              e.target.parent !== null
            ) {
              console.log("key no press // select just one");
  
              // line func dlg update
              if (this.parent.isLineDlgVisible) {
                if (e.target.attrs.pointId)
                  this.parent.addLineDlgInput(e.target.attrs.pointId);
              }
  
              this.parent.disablePropObj = false;
              this.parent.disablePropGroup = false;
  
              this._addTrNodes(
                [e.target],
                "click tap : key no press // select just one"
              );
  
              setTimeout(() => {
                this._updatePropObj(e.target);
              }, this.EVT_SLEEP_SECOND);
            } else {
              // is not kObj
              console.log("is not kObj");
              this.parent.disablePropObj = true;
            }
          } else if (metaPressed && isSelected) {
            // if we pressed keys and node was selected
            // we need to remove it from selection:
            const nodes = this.transformer.nodes().slice(); // use slice to have new copy of array
            // remove node from array
            nodes.splice(nodes.indexOf(e.target), 1);
            e.target.activeSelection(false);
  
            this._addTrNodes(
              nodes,
              "click tap : ctrl + click remove node from array",
              "notAll"
            );
          } else if (!metaPressed && !isSelected) {
            if (e.target.attrs.name.indexOf("_anchor") > -1) return;
  
            // add the node into selection
            const nodes = this.transformer.nodes().concat([e.target]);
            nodes.forEach((el) => {
              if (!el.isSelected) el.activeSelection(true);
            });
            if (nodes.length === 1) {
              // this.transformer.attrs.metaKeySortFlag = true;
  
              this.parent.disablePropObj = false;
              this.parent.disablePropGroup = false;
  
              setTimeout(() => {
                this._updatePropObj(nodes[0]);
              }, this.EVT_SLEEP_SECOND);
            }
  
            this._addTrNodes(nodes, "click tap : metaPressed + select", "notAll");
          }
        // }

      }.bind(this)
    );

    this.layer.add(this.transformer);
    this.tooltipLayer.add(this.tooltip);
    this.stage.add(this.layer);
    this.stage.add(this.tooltipLayer);

    this.layer.draw();
  }

  checkBayAttachment(){
    var nodes = this.layer.getChildren(function (node) {
      const name = node.attrs.name;
      if (name) {
        if (
          name !== "transformer" &&
          name !== "selectionRectangle" &&
          name !== "backgroundRect"
        ) {
          return node;
        }
      } else {
        return node;
      }
    });
    let allCheckBayAttach = () =>{
      let sensorList = [];
      let bayList = [];
      let _check = true;
      for(let node of nodes){
        if(node.attrs.isBayAttachment 
          && this.selectedShape.attrs.isBayAttachment == true){
          sensorList.push(node);
        }
        if(node.attrs.bayId){
          bayList.push(node);
        }
      }
      for(let sensor of sensorList){
        for(let bay of bayList){
          if(sensor.attrs.attachBayId == bay.attrs.bayId 
            && sensor.attrs.bayClass == bay.attrs.class){
              _check = this._haveIntersection(bay.getClientRect(),sensor.getClientRect());
              if(_check == false){
                return false;
              }
          }
        }
      }
      return _check;

    };
    if(this.isLocatingSensor == true){
      let flagBayAttch = false;
      if(this.selectedShape && this.selectedShape.attrs){
        if(this.selectedShape.attrs.isBayAttachment 
          && this.selectedShape.attrs.isBayAttachment == true){
          for(let node of nodes){
            if(node.attrs.bayId 
              && node.attrs.bayId == this.selectedShape.attrs.attachBayId 
              && node.attrs.class == this.selectedShape.attrs.bayClass){
              flagBayAttch = this._haveIntersection(node.getClientRect(), this.selectedShape.getClientRect());
            }
          }
        }
      }

      if(flagBayAttch == true && allCheckBayAttach() == true){
        this.isLocatingSensor = false; //if bay and sensor matched, unlock all other item from side menu
        EventBus.$emit('offLocatingSensor', 'true');
      }
    }
    else if(this.isLocatingSensor == false){
      let flagBayAttch = true;
      if(this.selectedShape && this.selectedShape.attrs){
        if(this.selectedShape.attrs.isBayAttachment && this.selectedShape.attrs.isBayAttachment == true){
          for(let node of nodes){
            if(node.attrs.bayId 
              && node.attrs.bayId == this.selectedShape.attrs.attachBayId
              && node.attrs.class == this.selectedShape.attrs.bayClass){
              flagBayAttch = this._haveIntersection(node.getClientRect(), this.selectedShape.getClientRect());
            }
          }
        }
      }
      if(flagBayAttch == false){
        this.isLocatingSensor = true;
        let data = {};
        data['bayId'] = this.selectedShape.attrs.attachBayId;
        data['sensorId'] = this.selectedShape.attrs.id;
        data['sensorName'] = this.selectedShape.attrs.className;
        data['sensorType'] = this.selectedShape.attrs.class;
        data['luId'] = this.selectedShape.attrs.luId;
        data['luName'] = this.selectedShape.attrs.luName;
        data['luType'] =  this.selectedShape.attrs.luType;
        data['bayClass'] = this.selectedShape.attrs.bayClass;
        EventBus.$emit('onLocatingSensor', data);
      }
    }

    this.selectedShape = null;
  }

  saveBayConfiguration(){
    var nodes = this.layer.getChildren(function (node) {
      const name = node.attrs.name;
      if (name) {
        if (
          name !== "transformer" &&
          name !== "selectionRectangle" &&
          name !== "backgroundRect"
        ) {
          return node;
        }
      } else {
        return node;
      }
    });
    
    let data = [];
    let filteredBayList = [];
    filteredBayList = nodes.filter(x => x.attrs.isBayAttachment || x.attrs.bayId);
    filteredBayList.forEach(x=>{
      if(x.isSelected){
        x.activeSelection(false);
      }
      if(x.attrs.isBayAttachment){
        for(let node of filteredBayList){
          if(node.attrs.bayId 
            && node.attrs.bayId == x.attrs.attachBayId
            && node.attrs.class == x.attrs.bayClass){
              x.setAttr('refBayX',x.getAbsolutePosition().x - node.getAbsolutePosition().x);
              x.setAttr('refBayY',x.getAbsolutePosition().y - node.getAbsolutePosition().y);
          }
        }
      }
    })
    filteredBayList.forEach(x=>{
      if(x.attrs.bayId){
        let drawInfoObj = {
          _Node: {},
          BayId: 0,
          MTRId: 0,
          SensorList: [] 
        }
        if(x.attrs.class == "BAY"){
          drawInfoObj.BayId = x.attrs.bayId;
        }
        else if(x.attrs.class == "MTR"){
          drawInfoObj.MTRId = x.attrs.bayId;
        }
        drawInfoObj._Node['refX']= 0;
        drawInfoObj._Node['refY']= 0;
        drawInfoObj._Node['nodeString'] = x.toJSON();
        for(let y of filteredBayList){
          if(y.attrs.isBayAttachment){
            if(y.attrs.attachBayId == x.attrs.bayId){
              let sensorAttrObj = {};
              sensorAttrObj['sensorId']=y.attrs.id;
              let nodeObj = {}
              nodeObj['refX'] = y.attrs.refBayX;
              nodeObj['refY'] = y.attrs.refBayY;
              nodeObj['nodeString'] =  y.toJSON();
              sensorAttrObj['Nodes'] = nodeObj;
              drawInfoObj.SensorList.push(sensorAttrObj);
            }
          }
        }
  
        data.push(drawInfoObj);
      }
    })

    return data;
  
  }

  /* Draw Edit Func */
  setDrawColor(color) {
    this.background.fill(color);
  }
  setDrawWidth(value) {
    let w = Number(value);
    this.background.width(w);
    this.stage.width(w);
  }
  setDrawHeight(value) {
    let h = Number(value);
    this.background.height(h);
    this.stage.height(h);
  }
  setDrawName(value) {
    console.log("setDrawName : " + value);
    this.stage.name(value);
    console.log(this.stage);
  }
  setPointInfo(info) {
    // Set Current Object Point info
    console.log("Set Current Object Point info");
    //console.log(info)
    if (this.selectedShape && this.selectedShape !== null) {
      console.log(info);
      if (info.fnInfo !== undefined && typeof info.fnInfo === "object") {
        this.selectedShape.attrs.fnInfo = info.fnInfo;
      } else {
        this.selectedShape.attrs.fnInfo = undefined;
      }

      if (info.trendInfo !== undefined && typeof info.trendInfo === "object") {
        this.selectedShape.attrs.trendInfo = info.trendInfo;
      } else {
        this.selectedShape.attrs.trendInfo = undefined;
      }

      this.selectedShape.attrs.pointName = info.pointName;
      this.selectedShape.attrs.pointId = parseInt(info.pointId);
      this.selectedShape.pointType(info.pointType);
      console.log(this.selectedShape);
    } else {
      console.log();
      return;
    }

    this._updatePropObj(this.selectedShape);

    //IF GROUP SELECTED ?

    /*
            nodes.forEach(el => {
                    if(!el.isSelected)
                        el.activeSelection(true)
                });
        */
  }
  clearPointInfo() {
    console.log("clearPointInfo");
    //console.log(this.selectedShape)
    // let group = null
    // console.log(group)
    // current > selectedShape
    //if(this.selectedShape && this.selectedShape !== null){

    // current Selected Group info ..  at transformer
    const nodes = this.transformer.nodes();

    for (let i = 0; i < nodes.length; i++) {
      if (nodes[i].attrs.fnInfo) {
        nodes[i].attrs.fnInfo = undefined;
      }
      if (nodes[i].attrs.trendInfo) {
        nodes[i].attrs.trendInfo = undefined;
      }

      nodes[i].attrs.pointName = "";
      nodes[i].attrs.pointId = 0;
      nodes[i].pointType(0);
    }

    console.log(nodes);
  }

  /* Toolbar Func */
  layering(action) {
    console.log("layering : " + action);
    //when selected item is exist
    const objArry = this.transformer.nodes();

    if (objArry && objArry.length > 0) {
      this.commandHelper.executeCommand(new LayeringCommand(objArry, action));
    } else {
      console.log("no selected items");
      return;
    }

    if (action === "bottom") {
      this.background.moveToBottom();
    }

    setTimeout(() => {
      this.stage.container().focus();
    }, 100);
  }
  sorting(action) {
    console.log("sorting : " + action);

    const objArry = this.transformer.nodes();

    if (objArry && objArry.length > 1) {
      this.commandHelper.executeCommand(
        new SortingCommand(
          objArry,
          action,
          this.transformer.attrs.metaKeySortFlag
        )
      );
    } else {
      console.log("no sorting items");
      return;
    }

    setTimeout(() => {
      this.stage.container().focus();
    }, 100);
  }
  //Add Object
  addObj(x, y, obj, isRestore) {
    console.log("addObj >");
    console.log(obj);

    let kObj;
    if (isRestore) {
      kObj = obj;
    } else if (obj.type === "Rect") {
      kObj = new Konva.Rect({
        // x: Number(x) - (obj.width /2),
        // y: Number(y) - (obj.height /2),
        x: Number(x) - obj.width / 2,
        y: Number(y) - obj.height / 2,
        name: obj.name,
        width: obj.width,
        height: obj.height,
        fill: obj.color,
        stroke: "#ffffff",
        strokeWidth: 1,
        draggable: true,
        strokeScaleEnabled: false,
      });
    } else if (obj.type === "Triangle") {
    /*
        else if( obj.type === 'Ellipse' ){

            kObj = new Konva.Ellipse({
                x: Number(x),
                y: Number(y),
                //offsetX:-10,
                //offsetY: -10,
                //radiusX: (Number(obj.points) / 2) - 5,
                //radiusY: (Number(obj.points) / 2) - 5,
                radiusX: Number(obj.points) / 2,
                radiusY: Number(obj.points) / 2,
                fill: '#ff0000',
                stroke: '#ffffff',
                strokeWidth: 1,
                draggable: true,
                strokeScaleEnabled: false
            });
        }
        */
      kObj = new Konva.Path({
        x: Number(x) - obj.width / 2,
        y: Number(y) - obj.height / 2,
        name: obj.name,
        width: obj.width,
        height: obj.height,
        data: obj.points,
        fill: "#ff0000",
        stroke: "#ffffff",
        strokeWidth: 1,
        draggable: true,
        strokeScaleEnabled: false,
      });
    } else if (obj.type === "Path" || obj.type === "Ellipse") {
      console.log('@@@dva this is path type@@@', obj);
      if(obj.name == "BAY" || obj.name == "MTR"){
        let _class = obj.name;
        kObj = new Konva.Path({
          x: Number(x) - obj.width / 2,
          y: Number(y) - obj.height / 2,
          // x: Number(x),
          // y: Number(y),
  
          //offsetX: obj.width / 2,
          //offsetY: obj.height / 2,
          // offsetX: 0,
          // offsetY: 0,
          name: obj.name,
          class: _class,
          width: obj.width,
          height: obj.height,
          data: obj.points,
          fill:  "#0000FF",
          stroke: "#8E8E8E",
          strokeWidth: 1,
          draggable: true,
          strokeScaleEnabled: false,
          //also need to set atributes for BAY/MTR from console, such as ID, Name of BAY/MTR 
          // scale: {
          //   x: 0.5,
          //   y: 0.5
          // }
        });
      }
      else
      {
        if(this.isLocatingSensor == true){
          console.log('execute adding more attributes for node');
          kObj = new Konva.Path({
            x: Number(x) - obj.width / 2,
            y: Number(y) - obj.height / 2,
            // x: Number(x),
            // y: Number(y),
    
            //offsetX: obj.width / 2,
            //offsetY: obj.height / 2,
            // offsetX: 0,
            // offsetY: 0,
            name: obj.name,
            width: obj.width,
            height: obj.height,
            data: obj.points,
            fill: obj.type === "Ellipse" ? "#ff0000" : "#8E8E8E",
            stroke: "#8E8E8E",
            strokeWidth: 1,
            draggable: true,
            strokeScaleEnabled: false,
            isBayAttachment: true, //to be checked if this sensor attached to a bay and check relative location
            attachBayId: this.sensorLocationInfo.bayId,
            className: this.sensorLocationInfo.sensorName,
            id: this.sensorLocationInfo.sensorId,
            class: this.sensorLocationInfo.sensorType,
            luId: this.sensorLocationInfo.luId,
            luName: this.sensorLocationInfo.luName,
            luType: this.sensorLocationInfo.luType,
            bayClass: this.sensorLocationInfo.bayClass
            //also set all attributes for className (sensorName), id (sensorId), class (sensorType, vd:SPDC), luId, luName
            // scale: {
            //   x: 0.5,
            //   y: 0.5
            // }
          });
        }
        else
        {
          kObj = new Konva.Path({
            x: Number(x) - obj.width / 2,
            y: Number(y) - obj.height / 2,
            // x: Number(x),
            // y: Number(y),
    
            //offsetX: obj.width / 2,
            //offsetY: obj.height / 2,
            // offsetX: 0,
            // offsetY: 0,
            name: obj.name,
            width: obj.width,
            height: obj.height,
            data: obj.points,
            fill: obj.type === "Ellipse" ? "#ff0000" : "#8E8E8E",
            stroke: "#8E8E8E",
            strokeWidth: 1,
            draggable: true,
            strokeScaleEnabled: false,
            // scale: {
            //   x: 0.5,
            //   y: 0.5
            // }
          });
        }

      }

    } else if (obj.type === "Line") {
      if (obj.name === "lineH") {
        kObj = new Konva.Line({
          name: obj.name,
          x: Number(x),
          y: Number(y),
          points: [0, 0, 100, 0],
          stroke: obj.color,
          strokeWidth: 4,
          draggable: true,
          closed:true,
          scaleX: 1,
          lineJoin: 'round'
        });
      } else if (obj.name === "lineV") {
        /*
                kObj = new Konva.Line({
                    x: Number(x),
                    y: Number(y),
                    points: [50, 0, 50, 100],
                    stroke: obj.color,
                    strokeWidth: 4,
                    draggable: true,
                    strokeScaleEnabled: false,

                });
                */

        kObj = new Konva.Line({
          name: obj.name,
          x: Number(x),
          y: Number(y),
          points: [0, 0, 50, 0],
          stroke: obj.color,
          strokeWidth: 4,
          draggable: true,
					closed:true,
          lineJoin: 'round',
          rotation: 90,
          scaleX: 1,
        });
      }
    } else if (obj.type === "Text") {
      const attr = this.selectionRectangle.attrs;

      if (attr.width < 10 && attr.height < 10) {
        console.log("no size text");
        return;
      }

      kObj = new Konva.Text({
        x: attr.x,
        y: attr.y,
        width: attr.width,
        height: attr.height,
        text: obj.text,
        fontSize: 16,
        fontFamily: "Arial",
        fontStyle: "normal",
        fill: "#ffffff",
        brUse: true,
        brFill: "#000000",
        brStroke: "#ffffff",
        brStrokeWidth: 1,
        align: "center",
        verticalAlign: "middle",
        draggable: true,
        strokeScaleEnabled: false,
      });
    } else if (obj.type === "Image") {
      // const attr = this.selectionRectangle.attrs;
      const attr = obj;

      if (attr.width < 10 && attr.height < 10) {
        console.log("no size text");
        return;
      }

      var imageObj = "";
      let fileName = "";
      if (obj.file !== undefined) {
        fileName = obj.file;

        imageObj = new Image();
        imageObj.onload = function () {
          kObj.width(attr.width);
          kObj.height(attr.height);
        };
        imageObj.src = obj.file;

      }

      kObj = new Konva.Image({
        x: Number(x) - obj.width / 2,
        y: Number(y) - obj.height / 2,
        width: attr.width,
        height: attr.height,
        image: imageObj,
        file: fileName,
        draggable: true,
        className: 'Image',
      });
      // this.transformer.moveToTop();

      imageObj.src = obj.file;
    }

    if (
      obj.name === "D_WIER" ||
      obj.name === "Y_WIER" ||
      obj.name === "lineV" ||
      obj.name === "lineH" ||
      obj.name === "lineTri" ||
      obj.name === "PT"
    ) {
      kObj.attrs.name = obj.name + "_" + kObj._id;
    } else {
      //set new name
      kObj.attrs.name = kObj.className + "_" + kObj._id;
    }

    this._bindObjEvt(kObj);

    console.log("addObj <");
    console.log(kObj);

    this.layer.add(kObj);

    if (!isRestore) {
      this.selectedShape = kObj;

      // command
      this.commandHelper.executeCommand(new AddObjCommand([kObj]));

      // NEW LINE ADD ERROR WHEN SIZE CHANGE
      //let e = {target : kObj, evt:{shiftKey : false,ctrlKey : false,metaKey : false}}

      //this._handleStageMouseDown(e)

      this.parent.disablePropObj = false;

      this._addTrNodes([kObj], "addObj : is not resotre");
      this._updatePropObj(kObj);

      this.transformer.moveToTop();

      setTimeout(() => {
        this.stage.container().focus();
      }, 100);
    }
    
    this.checkBayAttachment();
    
  }
  _bindObjEvt(kObj) {
    if (kObj.className === "Text") {
      kObj.on("transform", function () {
        this.setAttrs({
          width: Math.max(this.width() * this.scaleX(), 20), // MIN_WIDTH = 20
          height: Math.max(this.height() * this.scaleY(), 20), // MIN_WIDTH = 20
          scaleX: 1,
          scaleY: 1,
        });
      });
    } else if (kObj.className === "Line") {


      // kObj.on("transformend", () => {
      //   const oldPoints = kObj.points();
      //   const newPoints = [];
      //   const scaleX = kObj.scaleX();
      //   const scaleY = kObj.scaleY();
      //   for (var i = 0; i < oldPoints.length / 2; i++) {
      //     const point = kObj.getTransform().point({
      //       x: oldPoints[i * 2],
      //       y: oldPoints[i * 2 + 1],
      //     });
      //     newPoints.push(point.x / scaleX, point.y / scaleY);
      //   }
      //   kObj.points(newPoints);
      //   kObj.x(0);
      //   kObj.y(0);
      //   layer.draw();
      // });


      // kObj.on("transformend", () => {
      //   const oldPoints = kObj.points();
      //   const newPoints = [];
      //   const scaleX = kObj.scaleX();
      //   const scaleY = kObj.scaleY();
      //   for (var i = 0; i < oldPoints.length / 2; i++) {
      //     const point = kObj.getTransform().point({
      //       x: oldPoints[i * 2],
      //       y: oldPoints[i * 2 + 1],
      //     });
      //     newPoints.push(point.x / scaleX, point.y / scaleY);
      //   }
      //   kObj.points(newPoints);
      //   kObj.x(0);
      //   kObj.y(0);
      //   layer.draw();
      // });

    }



    kObj.on(
      "mouseenter",
      function () {
        if (this.currReady4CreateObj === "none") {
          this.stage.container().style.cursor = "move";
        }

        // console.log(kObj)
        if (kObj.className === "Line") {
          //console.log("This is line!!")
          // console.log(kObj)
          if (kObj.attrs.lineConditionArr) {
            let str = "Line Mapped - \n";
            let substr = "";
            for (let i = 0; i < kObj.attrs.lineConditionArr.length; i++) {
              if (kObj.attrs.lineConditionArr[i]) {
                substr +=
                  "(Condition " +
                  (i + 1) +
                  ":" +
                  " Point " +
                  kObj.attrs.lineConditionArr[i] +
                  ")\n";
              }
            }
            str += substr;
            //console.log(str)
            var mousePos = this.stage.getPointerPosition();
            this.tooltip.text(str);
            let tootipW = this.tooltip.width();
            let tootipX = mousePos.x;

            const stageW = this.stage.width();

            if (tootipX + tootipW > stageW) {
              tootipX = tootipX - (tootipX + tootipW - stageW) - 40;
            }

            this.tooltip.position({
              x: tootipX + 10,
              y: mousePos.y + 10,
            });

            this.tooltip.show();
          }
        }

        if (kObj.attrs.pointId) {
          var mousePos = this.stage.getPointerPosition();
          this.tooltip.text(
            "Point ID: " + kObj.attrs.pointId + " - " + kObj.attrs.pointName
          );

          let tootipW = this.tooltip.width();
          let tootipX = mousePos.x;

          const stageW = this.stage.width();

          if (tootipX + tootipW > stageW) {
            tootipX = tootipX - (tootipX + tootipW - stageW) - 40;
          }

          this.tooltip.position({
            x: tootipX + 10,
            y: mousePos.y + 10,
          });

          this.tooltip.show();
        }
      }.bind(this)
    );

    kObj.on(
      "mouseleave",
      function () {
        if (this.currReady4CreateObj === "none") {
          this.stage.container().style.cursor = "default";
        }

        if (this.tooltip !== undefined) {
          this.tooltip.hide();
        }
      }.bind(this)
    );

    kObj.on("dragstart",  function() {
      this.attrs.prevX = this.attrs.x;
      this.attrs.prevY = this.attrs.y;

      if (this.tooltip !== undefined) {
        this.tooltip.hide();
      }
      if(kObj.attrs.bayId){
        let nodes = this.parent.getChildren(function (node) {
          const name = node.attrs.name;
          if (name) {
            if (
              name !== "transformer" &&
              name !== "selectionRectangle" &&
              name !== "backgroundRect"
            ) {
              return node;
            }
          } else {
            return node;
          }
        });
        for(let node of nodes){
          if(node.attrs.isBayAttachment 
            && node.attrs.isBayAttachment == true 
            && node.attrs.attachBayId == kObj.attrs.bayId
            && node.attrs.bayClass == kObj.attrs.class ){
              node.startDrag(node);
          }
        }
      }
    });
  }
  _offObjEvt(kObj) {
    if (kObj.className === "Text" || kObj.className === "Line") {
      kObj.off("transform");
    }
    kObj.off("mouseenter");
    kObj.off("dragstart");
    kObj.off("mouseleave");
  }

  /* Func */
  command(action, value, type) {
    let objArry = this.transformer.nodes();

    let needForceUpdate = "none";

    // console.log('builder command : ' + action + ' / ' + value + ' / obj cnt : ' + objArry.length)
    // console.log(objArry)

    if (objArry.length === 0) {
      objArry = this.prevShapeGroup;
      if (objArry.length === 0) {
        objArry = this.prevShape;
      }
    }

    if (objArry.length === 0) return;

    if (action === "color") {
      /// property commnad
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "fill", value)
      );
    } else if (
      action === "x up" ||
      action === "y up" ||
      action === "x down" ||
      action === "y down"
    ) {
      /// arrow command
      let ret = this.commandHelper.executeCommand(
        new PositionCommand(objArry, action, value)
      );
    } else if (action === "x") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "x", parseInt(value))
      );
    } else if (action === "y") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "y", parseInt(value))
      );
    } else if (action === "opacity") {
      let opacityVal = Number(value);

      if (opacityVal <= 1) {
        //console.log(objArry[0].fill())
        //console.log(Konva.Util.getRGB(objArry[0].fill()))
        this.commandHelper.executeCommand(
          new SetOpacityCommand(objArry, "fill", opacityVal)
        );
        //this.commandHelper.executeCommand(new SetAttrCommand(objArry, 'opacity', opacityVal))
        //objArry[0].stroke('#ffffff')
      }
    } else if (action === "stroke") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "stroke", value)
      );
    } else if (action === "strokeWidth") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "strokeWidth", parseInt(value))
      );
    } else if (action === "dash") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "dash", value)
      );
    } else if (action === "width") {
      needForceUpdate = this.commandHelper.executeCommand(
        new SetAttrWidthCommand(objArry, parseInt(value), type)
      );
    } else if (action === "height") {
      needForceUpdate = this.commandHelper.executeCommand(
        new SetAttrHeightCommand(objArry, parseInt(value), type)
      );
    } else if (action === "degree") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "rotation", parseInt(value))
      );
    } else if (action === "stroke") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "stroke", value)
      );
    } else if (action === "strokeWidth") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "strokeWidth", parseInt(value))
      );
    } else if (action === "fontSize") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "fontSize", parseInt(value))
      );
    } else if (action === "fontStyle") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "fontStyle", value)
      );
    } else if (action === "fontFamily") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "fontFamily", value)
      );
    } else if (action === "align") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "align", value)
      );
    } else if (action === "verticalAlign") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "verticalAlign", value)
      );
    } else if (action === "brFill") {
      needForceUpdate = this.commandHelper.executeCommand(
        new SetBrAttrCommand(objArry, "brFill", value)
      );
    } else if (action === "brOpacity") {
      needForceUpdate = this.commandHelper.executeCommand(
        new SetBrOpacityCommand(objArry, "brFill", value)
      );
    } else if (action === "brStroke") {
      needForceUpdate = this.commandHelper.executeCommand(
        new SetBrAttrCommand(objArry, "brStroke", value)
      );
    } else if (action === "brStrokeWidth") {
      needForceUpdate = this.commandHelper.executeCommand(
        new SetBrAttrCommand(objArry, "brStrokeWidth", parseInt(value))
      );
    } else if (action === "extend") {
      this.commandHelper.executeCommand(
        new SetAttrCommand(objArry, "extend", value)
      );
    }

    if (needForceUpdate === "forceUpdate") {
      this.transformer.forceUpdate();
    }

    this.stage.container().focus();
  }
  getNodeInfoList() {
    var nodes = this.layer.getChildren(function (node) {
      const name = node.attrs.name;
      if (name) {
        if (
          name !== "transformer" &&
          name !== "selectionRectangle" &&
          name !== "backgroundRect"
        ) {
          return node;
        }
      } else {
        return node;
      }
    });

    let nodeArr = [];

    nodes.forEach((element) => {
      if (element.isSelected) {
        element.activeSelection(false);
      }
      nodeArr.push(element.toJSON());
    });

    return nodeArr;
  }
  getDrawInfo() {
    return {
      name: this.stage.name(),
      //width:  this.stage.width(),
      //height: this.stage.height(),
      backgroundColor: this.background.fill(),
    };
  }
  initDraw(drawInfo) {
    console.log("initDefaultDraw");
    console.log(drawInfo);

    this._destroyShapes();
    this._addTrNodes([], "initDraw : input []");
    // default darw option set

    if (drawInfo) {
      // set draw info stage
      this.setDrawName(drawInfo.name);
      this.setDrawWidth(drawInfo.width);
      this.setDrawHeight(drawInfo.height);
      this.setDrawColor(drawInfo.backgroundColor);

      this.parent.drawName = drawInfo.name;
      this.parent.drawWidth = drawInfo.width;
      this.parent.drawHeight = drawInfo.height;
      this.parent.drawColor = drawInfo.backgroundColor;

      this.stage.scale({ x: 1, y: 1 });

      this._loadDrawNodes(drawInfo.nodes);
    } else {
      this._initDefaultDraw();
    }
  }
  

  
  updateTextNodePosition() {
    var nodes = this.layer.getChildren(node => {
      const name = node.attrs.name;
      return !(name === "transformer" || name === "selectionRectangle" || name === "backgroundRect");
    });
  
    nodes.forEach(node => {
      if (node.attrs.class === "BAY") {
        let bayNode = node;
        let textNode = nodes.find(n => n.attrs.isBayName && n.attrs.text === bayNode.attrs.bayName && n.attrs.linkedBayId === bayNode.attrs.bayId);
  
        if (textNode) {
          // Apply drag functionality
          bayNode.on('dragmove', function () {
            const bayNodeRect = this.getClientRect(); // Recalculate on each drag event
            const centerX = bayNodeRect.x + bayNodeRect.width / 2;
            const textWidth = textNode.width();
            const textHeight = textNode.height();
  
            textNode.position({
              x: centerX - textWidth / 2,
              y: bayNodeRect.y - textHeight 
            });
  
            this.getLayer().batchDraw(); // Redraw the layer
          });
  
          // Initial position of the text node
          bayNode.fire('dragmove'); // Use this to initially position the text node
        }
      }

      if (node.attrs.class === "MTR") {
        let mtrNode = node;
        let textNode = nodes.find(n => n.attrs.isMTRName && n.attrs.text === mtrNode.attrs.bayName && n.attrs.linkedMTRId === mtrNode.attrs.bayId);
        let backgroundShape = nodes.find(n => n.attrs.isMTRBackgroundShape && n.attrs.linkedMTRId === mtrNode.attrs.bayId);
        console.log('mtr condition ',textNode)
  
        if (textNode) {
          // Apply drag functionality
          mtrNode.on('dragmove', function () {
            const mtrNodeRect = this.getClientRect(); // Recalculate on each drag event
            const centerX = mtrNodeRect.x + mtrNodeRect.width / 2;
  
            // Update positions
            textNode.position({
              x: centerX - textNode.width() / 2,
              y: mtrNodeRect.y - textNode.height() - 30
            });
            backgroundShape.position({
              x: centerX - backgroundShape.width() / 2,
              y: mtrNodeRect.y - backgroundShape.height() + 60
            });
  
            this.getLayer().batchDraw(); // Redraw the layer
          });
  
          // Initial position of the text node
          mtrNode.fire('dragmove'); // Use this to initially position the text node
        }
      }
    });
  
    console.log('updateTextNodePosition', nodes);
    this.layer.batchDraw();
  }
  

  _loadDrawNodes(nodes) {

    nodes.forEach((node) => {

      console.log('node', JSON.parse(node));

        let obj = Konva.Node.create(node);
      // Generate Point Name
      if (this.PointList === []) {
        alert("포인트 정보 업데이트가 필요합니다. [ _loadDrawNodes Failed ]");
        return;
      }
      if (obj.attrs.pointType !== 5 && obj.attrs.pointType !== 6) {
        //기능:5 트렌드:6
        let pId = obj.attrs.pointId;
        if (pId !== undefined && pId > 0) {
          let p = this.PointList[pId - 1];

          if (p) {
            obj.attrs.pointName = p.pointName;
          }
        }
      }

      
      this._bindObjEvt(obj);
      this.layer.add(obj);
    });

    /* Image Load */
    this.layer.getChildren(function (node) {
      if (node.className === "Image") {
        var imageObj = new Image();
        imageObj.src = node.attrs.file;
        imageObj.onload = function () {
          node.draw();
        };
        node.attrs.image = imageObj;
      }
    });

    setTimeout(() => {
      this.layer.draw();
    }, 1000);

    this.layer.batchDraw();
    this.updateTextNodePosition();
  }
  deleteDraw() {}
  _destroyShapes() {
    var nodes = this.layer.getChildren(function (node) {
      const name = node.attrs.name;
      if (name) {
        if (
          name !== "transformer" &&
          name !== "selectionRectangle" &&
          name !== "backgroundRect"
        ) {
          return node;
        }
      } else {
        return node;
      }
    });

    nodes.forEach((element) => {
      element.destroy();
    });
  }
  _initDefaultDraw() {
    console.log("_initDefaultDraw");

    this.stage.width(this.op.width);
    this.stage.height(this.op.height);
    this.stage.name("NewDraw");

    this.background.width(this.op.width);
    this.background.height(this.op.height);
    this.background.fill(this.op.drawColor);

    this.parent.drawName = "NewDraw";
    this.parent.drawWidth = this.op.width;
    this.parent.drawHeight = this.op.height;
    this.parent.drawColor = this.op.drawColor;

    this.stage.scale({ x: 1, y: 1 });
  }
  switchTrAnchor(mode) {
    let isLine;

    if (mode === "default") {
      isLine = false;
    } else {
      isLine = mode === "Line";
    }

    if (isLine) {
      this.transformer.attrs.ignoreStroke = false;
      this.transformer.enabledAnchors(["middle-right", "middle-left"]);
      this.transformer.borderEnabled(false);
      // this.transformer.keepRatio(true); 
    } else {
      this.transformer.attrs.ignoreStroke = true;
      this.transformer.enabledAnchors([
        "top-left",
        "top-center",
        "top-right",
        "middle-right",
        "middle-left",
        "bottom-left",
        "bottom-center",
        "bottom-right",
      ]);
      this.transformer.borderEnabled(true);
    }
  }

  /* Inner Func */
  _updatePropObj(target) {
    if (target === undefined) return;

    console.log("_updatePropObj  : " + target.className);
    //console.log(target)
    //console.log(target.className === 'Text')

    // property enable flag
    this.parent.disableLineSize = true;

    // attrs binding
    const attrs = target.attrs;

    this.parent.propObjName = attrs.name ? attrs.name : "No Name";

    if (attrs.pointId) this.parent.propObjPointNum = attrs.pointId;
    else this.parent.propObjPointNum = "";

    this.parent.propObjPointName = attrs.pointName ? attrs.pointName : "-";

    this.parent.propObjX = parseInt(attrs.x);
    this.parent.propObjY = parseInt(attrs.y);

    if (!attrs.scaleX) attrs.scaleX = 1;
    if (!attrs.scaleY) attrs.scaleY = 1;

    if (target.className === "Text") {
      this.parent.textObjNameDp = attrs.text;

      this.parent.textObjFillStrokeUse = attrs.brUse
        ? "accepted"
        : "not_accepted";
      this.parent.textObjFontSize = attrs.fontSize;
      this.parent.textObjFontFamily = attrs.fontFamily;
      this.parent.textObjFontStyle = attrs.fontStyle;
      this.parent.textObjAlignH = attrs.align;
      this.parent.textObjAlignV = attrs.verticalAlign;

      //this.parent.textObjFill = attrs.brFill
      if (attrs.brFill) {
        if (attrs.brFill.length > 8) {
          //Update Property : RGBA > HEX ( only display )

          let rgba = Konva.Util.colorToRGBA(attrs.brFill);
          let color = "#" + Konva.Util._rgbToHex(rgba.r, rgba.g, rgba.b);
          this.parent.textObjFill = color;
          this.parent.$refs.textObjFill.localValue = color;

          // no border effect //
          this.parent.textObjOpacity = rgba.a;
        } else {
          this.parent.textObjFill = attrs.brFill;
          this.parent.$refs.textObjFill.localValue = attrs.brFill;
          //this.parent.textObjOpacity = attrs.textObjOpacity ? attrs.textObjOpacity : 1  // before
          this.parent.textObjOpacity = 1; // before
        }
      }

      this.parent.textObjStroke = attrs.brStroke;
      this.parent.textObjStrokeWidth = attrs.brStrokeWidth;
    }

    // this.parent.propObjWidth = parseInt(scaleWidth)
    // this.parent.propObjHeight = parseInt(scaleHeight)
    let cR = target.getClientRect({ skipStroke: true });

    if (target.className === "Line") {
      this.parent.disableLineSize = false;

      if (attrs.name.split("_")[0] === "lineV") {
        this.parent.propObjWidth = parseInt(cR.height);
      } else {
        this.parent.propObjWidth = parseInt(cR.width);
        this.parent.propObjHeight = parseInt(cR.height);
      }

      this.parent.lineFuncUse =
        attrs.lineFuncUse === undefined ? false : attrs.lineFuncUse;
    } else {
      this.parent.propObjWidth = parseInt(cR.width);
      this.parent.propObjHeight = parseInt(cR.height);
    }

    this.parent.propObjDegree = attrs.rotation ? parseInt(attrs.rotation) : 0;

    if (attrs.fill) {
      if (attrs.fill.length > 8) {
        //Update Property : RGBA > HEX ( only display )

        let rgba = Konva.Util.colorToRGBA(attrs.fill);
        //console.log(rgba)
        //console.log( '#' + Konva.Util._rgbToHex(rgba.r,rgba.g,rgba.b))

        this.parent.propObjColor =
          "#" + Konva.Util._rgbToHex(rgba.r, rgba.g, rgba.b);

        // no border effect //
        this.parent.propObjOpacity = rgba.a;
      } else {
        this.parent.propObjColor = attrs.fill;
        this.parent.propObjOpacity = attrs.opacity ? attrs.opacity : 1; // before
      }
    }

    this.parent.propObjStrokeWidth = attrs.strokeWidth;

    this.parent.propObjStroke = attrs.stroke;
    this.parent.propObjDash = attrs.dash ? attrs.dash : [];

    this.parent.extendType = attrs.extend ? attrs.extend.type : "none";

    if (this.parent.extendType === "none") {
      // init extend prop
      this.parent.extendMin = 0;
      this.parent.extendMax = 0;
      this.parent.extendTemplate = "";
      this.parent.extendPdName = "";
      this.parent.extendOffsetLine = "";
    } else {
      this.parent.extendMin = attrs.extend.min;
      this.parent.extendMax = attrs.extend.max;
      this.parent.extendTemplate = attrs.extend.extendTemplate;
      this.parent.extendPdName = attrs.extend.extendPdName;
      this.parent.extendOffsetLine = attrs.extend.extendOffsetLine;
    }
  }
  _handleStageMouseUp(e) {
    console.log("_handleStageMouseUp",e);
    //console.log(this.prevShape)
    this.checkBayAttachment();
    if (this.currReady4CreateObj === "text") {
      this.addObj(0, 0, { type: "Text", text: this.parent.textObjName });
      this.stage.container().style.cursor = "default";
      this.currReady4CreateObj = "none";
      this.parent.textObjName = "";
    } else if (this.currReady4CreateObj === "img") {
      console.log("create obj image");
      //console.log(this.parent.imgObjFile)

      this.addObj(0, 0, { type: "Image", file: this.parent.currImgName });

      this.stage.container().style.cursor = "default";
      this.currReady4CreateObj = "none";

      /* Blob file -> path to 'static/upload/'  [POST] Req API  */

      //webkitRelativePath
      //var fileBuffer = new Buffer.from(this.parent.imgObjFile, 'base64')
      //console.log(fileBuffer)

      /*
            var fs = require('fs');
            console.log(fs)

            //var imageBuffer = request.file.buffer;
            var imageName = 'static/images/map.png';

            //fs.createWriteStream(imageName).write(imageBuffer);
            fs.createWriteStream(imageName).write(this.parent.imgObjFile.arrayBuffer);
            */
    }
  }
  _handleStageMouseDown(e) {
    console.log("handleStageMouseDown > " + e.target.className);
    console.log(e.target);

    console.log(e.target.getClientRect({ skipStroke: true }));
    if (e.target.className) console.log(e.target.getSelfRect());

    this.selectedShape = null;

    if (e.target === e.target.getStage()) {
      /// clicked on stage - clear selection
      //this._updateTransformer(e);
      return;
    }

    //console.log('parent name')
    //console.log(e.target.getParent().className)

    /// clicked on transformer - do nothing
    const clickedOnTransformer =
      e.target.getParent().className === "Transformer";
    if (clickedOnTransformer) {
      this.currAnchor = e.target.attrs.name;
      return;
    }

    // find clicked rect by its
    this.selectedShape = e.target;
    this.prevShape = e.target;

    //console.log('selectedShape')
    //console.log(e.target)

    this._updateTransformer(e);
  }
  // _handleStageMouseDbClick(e) {
  //   console.log("_handleStageMouseDbClick > " + e.evt.which);
  //   console.log('this is e.target', e.target);

  //   console.log('this is e.evt' , e.evt); // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

  //   console.log("_handleStageMouseDbClick < ");

  //   if (e.evt.which === 3) {
  //     e.evt.preventDefault();
  //     return;
  //   }



  //   if (e.target.parent !== this.transformer && e.target.parent !== null) {
  //     const info = {
  //       enable: true,
  //       left: e.evt.clientX,
  //       top: e.evt.clientY,
  //       pointId: e.target.attrs.pointId,
  //       width: e.target.attrs.width,
  //       height: e.target.attrs.height,
  //     };

  //     // Img X // lineTri O
  //     if (
  //       e.target.className === "Line" ||
  //       e.target.attrs.name.indexOf("lineTri") > -1 ||
  //       e.target.attrs.name.indexOf("D_WIER") > -1 ||
  //       e.target.attrs.name.indexOf("Y_WIER") > -1 ||
  //       e.target.attrs.name.indexOf("PT") > -1
  //     ) {
  //       console.log("showLineDlg >>>");
  //       this.parent.showLineDlg(info);
  //     } else {
  //       if (!this.parent.disablePropGroup) {
  //         this.parent.showPointDlg(info); // this.parent.showPointDlg()
  //       }
  //     }
  //   }
  // }


  // /// HANDLE DBCLICK FUNCTION FOR PDA ////
  _handleStageMouseDbClick(e) {
    console.log("_handleStageMouseDbClick > " + e.evt.which);
    console.log('this is e.target', e.target.attrs);
  
    console.log('this is e.evt' , e.evt, this.isLocatingSensor); // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  
    console.log("_handleStageMouseDbClick < ");
    console.log('@@@@@@@@@@@@@@@@console logging selected nodes when double clicked', selectedNodes)
  
    if (e.evt.which === 3) {
      e.evt.preventDefault();
      return;
    }
    if(e.target.attrs && e.target.attrs.isBayAttachment){
      console.log('no dialog');
      return
    }
  
    if (e.target.parent !== this.transformer && e.target.parent !== null) {
      const info = {
        enable: true,
        left: e.evt.clientX,
        top: e.evt.clientY,
        pointId: e.target.attrs.pointId,
        width: e.target.attrs.width,
        height: e.target.attrs.height,
      };
  
      let MLU = false;
      let GLU = false;

      let gluSPDC = sensorSymbols[0].points
      let SCBR = sensorSymbols[1].points
      let mluSPDC = sensorSymbols[2].points
      let SLTC = sensorSymbols[3].points
      let SBSH = sensorSymbols[4].points
      let SIML = sensorSymbols[5].points
      let BAY = sensorSymbols[6].points
      let MTR = sensorSymbols[7].points
  
      let isSPDCmlu = false;
      let isSPDCglu = false;
      let isSCBR = false;
      let isSIML = false;
      let isSBSH = false;
      let isSLTC = false;
      let isBAY = false;
      let isMTR = false;
      let selectedShape = e.target;


      switch (e.target.attrs.data) {
        case gluSPDC:
          GLU = true;
          isSPDCglu = true;
          break;
        case SLTC:
          MLU = true;
          isSLTC = true;
          break;
        case SBSH:
          MLU = true;
          isSBSH = true;
          break;
        case SIML:
          MLU = true;
          isSIML = true;
          break;
        case mluSPDC:
          MLU = true;
          isSPDCmlu = true;
          break;
        case SCBR:
          GLU = true;
          isSCBR = true;
          break;
        case BAY:
          GLU = true;
          isBAY = true;
          break;
        case MTR:
          MLU = true;
          isMTR = true;
          break;
      }

      
      if (!this.parent.disablePropGroup && (MLU || GLU) &&(!isBAY&&!isMTR)) {
        EventBus.$emit('updateMLUAndGLU', {MLU, GLU, isSPDCmlu, isSPDCglu, isSCBR, isSIML, isSBSH, isSLTC, isBAY, isMTR, selectedShape});
        console.log('This is the selected shape', selectedShape);
        this.parent.showPointDlg(info);
      }
      else if(!this.parent.disablePropGroup && (MLU || GLU) &&(isBAY||isMTR)){
        EventBus.$emit('updateMLUAndGLU', {MLU, GLU, isSPDCmlu, isSPDCglu, isSCBR, isSIML, isSBSH, isSLTC, isBAY, isMTR, selectedShape});
        console.log('This is the selected shape bay/mtr', selectedShape);
        this.parent.showBayDialog(info, isBAY, isMTR);
      }
      else if (!this.parent.disablePropGroup && selectedNodes.length > 4){
        console.log('test for considering if it should be bay or not')
      }
    }
  }

  _saveSelectedNodesAsImage() {
    if (selectedNodes.length === 0) {
      console.error('No selected nodes to save.');
      return;
    }
  
    const transformerBoundingBox = this.transformer.getClientRect();
  
    if (transformerBoundingBox.width === 0 || transformerBoundingBox.height === 0) {
      console.error('Transformer bounding box has zero width or height.');
      return;
    }
  
    const offScreenCanvas = document.createElement('canvas');
    offScreenCanvas.width = transformerBoundingBox.width;
    offScreenCanvas.height = transformerBoundingBox.height;
  
    const tempStage = new Konva.Stage({
      container: offScreenCanvas,
      width: transformerBoundingBox.width,
      height: transformerBoundingBox.height,
    });
  
    const tempLayer = new Konva.Layer();
    tempStage.add(tempLayer);
  
    selectedNodes.forEach(node => {
      const copy = node.clone({
        x: node.x() - transformerBoundingBox.x,
        y: node.y() - transformerBoundingBox.y
      });
      tempLayer.add(copy);
    });
  
    tempLayer.batchDraw(); // Ensure all drawings are rendered
  
    setTimeout(() => {
      try {
        const dataURL = tempStage.toDataURL({
          mimeType: 'image/png',
          quality: 1.0
        });
  
        if (!dataURL) {
          throw new Error('Failed to generate image URL.');
        }
  
        const link = document.createElement('a');
        link.href = dataURL;
        link.download = 'bay.png';
        document.body.appendChild(link);
        link.click();
        document.body.removeChild(link);
      } catch (error) {
        console.error('Error while saving image:', error);
      }
    }, 500); // Increased timeout to ensure rendering is complete
  }
  
  
  
  

  
////  
  _addTrNodes(nodes, callStack, action) {
    console.log("@@@ _addTrNodes >> " + callStack + " >> action : " + action);
    console.log(nodes);
    selectedNodes = nodes;

    // inActive prev nodes
    if (action !== "notAll") {
      var shapes = this.layer.getChildren((node) => {
        const name = node.name();
        return (
          name !== "backgroundRect" &&
          name !== "selectionRectangle" &&
          name !== "transformer"
        );
      });

      shapes.forEach((el) => {
        if (el.isSelected) el.activeSelection(false);
      });
    }

    if (nodes === undefined || nodes.length === 0) {
      this.transformer.nodes([]);
      return;
    }

    if (action === "groupDrag") {
      nodes.forEach((el) => {
        if (!el.isSelected) el.activeSelection(false);
      });
    }

    this.parent.disableTextObj = false;
    this.parent.showPropObjStroke = true;
    this.parent.showPropObjColor = true;
    this.parent.disableLineFunc = true;

    this.switchTrAnchor("default");

    if (nodes.length > 1) {
      //console.log('nodes[] <= nodes')

      let isAllText = true;
      let textObjCnt = 0;

      // text property disable flag
      for (let index = 0; index < nodes.length; index++) {
        const element = nodes[index];
        if (element.className === "Text") {
          textObjCnt++;
        }
      }
      if (nodes.length !== textObjCnt) {
        isAllText = false;
      }

      if (isAllText) {
        console.log("isAllText");

        this.parent.showPropObjStroke = false;

        this.parent.showPropObjColor = false;
      } else {
        //console.log('isNotAllText text cnt : ' + textObjCnt + this.parent.showPropObjStroke)
        this.parent.disableTextObj = true;

        if (textObjCnt > 0) {
          this.parent.showPropObjStroke = false;
        }
      }
    } else if (nodes.length === 1) {
      //console.log('nodes[] <= node')
      let node;
      if (Array.isArray(nodes)) {
        node = nodes[0];
      } else {
        node = nodes;
      }

      if (node.className === "Text") {
        this.parent.showPropObjStroke = false;
        this.parent.disableTextObj = false;
        this.parent.showPropObjColor = false;
      } else {
        if (node.className === "Line") {
          this.switchTrAnchor("Line");
          this.parent.disableLineFunc = false;
          this.parent.showPropObjColor = false;
        }
        this.parent.disableTextObj = true;
      }
    }

    // >>  prev
    this.transformer.nodes(nodes);
    // <<

    //this.layer.toggleHitCanvas()
  }
  _updateTransformer(e) {
    // do nothing if selected node is already attached
    if (this.selectedShape === this.transformer) {
      console.log("do nothing if selected node is already attached");
      return;
    }
    if(e.evt.shiftKey || e.evt.ctrlKey || e.evt.metaKey){
      return
    }

    if (this.selectedShape) {
      // attach to another node
      //console.log( 'attach to another node' )
      //console.log( this.selectedShape )
      //this.transformer.nodes([this.selectedShape]);
    } else {
      // remove transformer
      this._addTrNodes([], "_updateTransformer : input []");
    }

    this.transformer.moveToTop();
  }
  _getCorner(pivotX, pivotY, diffX, diffY, angle) {
    const distance = Math.sqrt(diffX * diffX + diffY * diffY);

    /// find angle from pivot to corner
    angle += Math.atan2(diffY, diffX);

    /// get new x and y and round it off to integer
    const x = pivotX + distance * Math.cos(angle);
    const y = pivotY + distance * Math.sin(angle);

    return { x: x, y: y };
  }
  _getClientRect(rotatedBox) {
    const { x, y, width, height } = rotatedBox;
    const rad = rotatedBox.rotation;

    const p1 = this._getCorner(x, y, 0, 0, rad);
    const p2 = this._getCorner(x, y, width, 0, rad);
    const p3 = this._getCorner(x, y, width, height, rad);
    const p4 = this._getCorner(x, y, 0, height, rad);

    const minX = Math.min(p1.x, p2.x, p3.x, p4.x);
    const minY = Math.min(p1.y, p2.y, p3.y, p4.y);
    const maxX = Math.max(p1.x, p2.x, p3.x, p4.x);
    const maxY = Math.max(p1.y, p2.y, p3.y, p4.y);

    return {
      x: minX,
      y: minY,
      width: maxX - minX,
      height: maxY - minY,
    };
  }
  _containerKeydown(e) {
    if (e.shiftKey) {
      // 임시 >> 추후 스케일 Command 적용

      if (e.which == 37) {
        // left
        // const nodes = this.transformer.nodes()
        // this.commandHelper.executeCommand(new SetAttrWidthCommand( nodes, -1, 'dec' )) //increase decrease
        this.command("width", -1, "dec");
      } else if (e.which == 38) {
        // up
        // const nodes = this.transformer.nodes()
        // this.commandHelper.executeCommand(new SetAttrHeightCommand( nodes, -1, 'inc' )) //increase decrease
        this.command("height", -1, "inc");
      } else if (e.which == 39) {
        // right
        //const nodes = this.transformer.nodes()
        //this.commandHelper.executeCommand(new SetAttrWidthCommand( nodes, 1, 'inc' ))
        this.command("width", 1, "inc");
      } else if (e.which == 40) {
        // down
        // const nodes = this.transformer.nodes()
        // this.commandHelper.executeCommand(new SetAttrHeightCommand( nodes, 1, 'dec' )) //increase decrease
        this.command("height", 1, "dec");
      }

      e.preventDefault();
      return;
    }

    let xyShape = null;
    if (this.selectedShape !== null) {
      xyShape = this.selectedShape;
    } else {
      xyShape = this.prevShape;
    }

    let DELTA = 10;

    if (e.ctrlKey) DELTA = 1;

    if (e.keyCode === 37) {
      // left

      //xyShape.x(xyShape.x() - DELTA);
      this.command("x down", parseInt(DELTA));
    } else if (e.keyCode === 38) {
      // down
      //xyShape.y(xyShape.y() - DELTA);
      this.command("y down", parseInt(DELTA));
    } else if (e.keyCode === 39) {
      // right
      //xyShape.x(xyShape.x() + DELTA);
      this.command("x up", parseInt(DELTA));
    } else if (e.keyCode === 40) {
      // up
      //xyShape.y(xyShape.y() + DELTA);
      this.command("y up", parseInt(DELTA));
    } else if (e.ctrlKey) {
      // Ctrl + Key

      //let testmode = true // clip board func
      let testmode = true; // clip board func

      if (e.keyCode === 67) {
        // ctrl + c
        console.log("ctrl + c");

        if (testmode) {
          //clip board function

          let tmpArr = [];

          this.transformer.nodes().forEach((node) => {
            node.activeSelection(false);
            let clone = node.clone();
            tmpArr.push(clone);
          });

          this.parent.setClipboardBG(tmpArr);
        } else {
          this.tempCopyRepo = this.transformer.nodes();
        }

        ////////////////////
        // /* default is not use vuex */
        // this.tempCopyRepo = null
        // this.tempCopyRepo = this.transformer.nodes()
      } else if (e.keyCode === 86) {
        // ctrl + v

        console.log("ctrl + v");

        let nodes;

        if (testmode) {
          let tmpArr = this.parent.$store.state.clipboardBG;
          nodes = tmpArr;
        } else {
          /* default is not use vuex */
          if (this.tempCopyRepo === null) return;
          nodes = this.tempCopyRepo;
        }

        let tmp = [];

        nodes.forEach((element) => {
          if (element.isSelected) {


            if (element.className === "Text") {
              // element._activeSelection(false);
              var clone = element.clone({
                x: element.x() + 30
              });

            } else {
              // element.activeSelection(false);
              var clone = element.clone({
                x: element.x() + 30
              });
            }


          }

          // var clone = element.clone({
          //   x: element.x() + 30,
          //   // activeStroke: { stroke: '#F6CB01', strokeWidth: 3 },
          //   // isSelected: false
          //   //y: element.y() + 15
          // });

          tmp.push(clone);

          //set new name
          if (clone.attrs.name.indexOf("_") > -1) {
            clone.attrs.name = clone.attrs.name.split("_")[0] + "_" + clone._id;
          } else {
            clone.attrs.name = clone.className + "_" + clone._id;
          }

          this._offObjEvt(clone);
          this._bindObjEvt(clone);
          //clone.activeSelection(true)

          this.layer.add(clone);
        });

        this.commandHelper.executeCommand(new PasteCommand(nodes, tmp));
        this._addTrNodes(tmp, "keydown : ctrl + v", "groupDrag");

        if (tmp.length === 1) {
          this._updatePropObj(tmp[0]);
        }

        this.tempCopyRepo = tmp;

        this.transformer.moveToTop();
      } else if (e.keyCode === 88) {
        // ctrl + x
        console.log("ctrl + x");
        const nodes = this.transformer.nodes();
        this.commandHelper.executeCommand(new DeleteObjCommand(nodes));
        if(nodes[0].attrs.bayId){
          var sensorNodes = this.layer.getChildren(function (node) {
            const name = node.attrs.name;
            if (name) {
              if (
                name !== "transformer" &&
                name !== "selectionRectangle" &&
                name !== "backgroundRect"
              ) {
                return node.attrs.isBayAttachment && node.attrs.attachBayId == nodes[0].attrs.bayId && node.attrs.bayClass == nodes[0].attrs.class;
              }
            } else {
              return node.attrs.isBayAttachment && node.attrs.attachBayId == nodes[0].attrs.bayId && node.attrs.bayClass == nodes[0].attrs.class;
            }
          });
          sensorNodes.forEach(x=>x.destroy());
        }

        this.tempCopyRepo = [];

        nodes.forEach((element) => {
          var clone = element.clone({
            x: element.x() + 30,
            y: element.y() + 15,
          });

          this.tempCopyRepo.push(clone);
          element.destroy();
        });

        this._addTrNodes([], "keydown : ctrl + x");
      } else if (e.keyCode === 90) {
        // ctrl + z
        console.log("ctrl + z");
        // this.selectedShape  update  >>> ??
        //console.log(this.selectedShape)

        let resultObjects = this.commandHelper.undo();
        if (resultObjects === undefined) return;

        if (resultObjects === "empty") {
          this._addTrNodes(
            [],
            "keydown : ctrl + z commandHelper.undo() input []"
          );
        } else if (resultObjects.isRestore) {
          const objects = resultObjects.objects;

          objects.forEach((el) => {
            this.addObj(0, 0, el, resultObjects.isRestore);
          });

          this._addTrNodes(
            objects,
            "keydown : ctrl + z commandHelper.undo() restore"
          );

          setTimeout(() => {
            this.stage.container().focus();
          }, 100);
        } else if (resultObjects === "forceUpdate") {
          this.transformer.forceUpdate();
        } else if (resultObjects) {
          this._addTrNodes(
            resultObjects,
            "keydown : ctrl + z commandHelper.undo() default"
          );
        }
      } else if (e.keyCode === 65) {
        // ctrl + a
        console.log("All Select >>");

        this.transformer.attrs.metaKeySortFlag = false;

        console.log(this.transformer);

        let shapes = this.layer.getChildren((node) => {
          return (
            node.name() !== "backgroundRect" &&
            node.name() !== "selectionRectangle" &&
            node.className !== "Transformer"
          );
        });

        this._addTrNodes(shapes, "keydown : ctrl + a all selected");
      } else if (e.keyCode === 83) {
        // ctrl + s
        console.log("ctrl + s"); // save
        this.parent.toolDrawFunc("save");
      }
    } else if (e.keyCode === 46) {
      // Delete

      const nodes = this.transformer.nodes();

      this.commandHelper.executeCommand(new DeleteObjCommand(nodes));
      if(nodes[0].attrs.bayId){
        var sensorNodes = this.layer.getChildren(function (node) {
          const name = node.attrs.name;
          if (name) {
            if (
              name !== "transformer" &&
              name !== "selectionRectangle" &&
              name !== "backgroundRect"
            ) {
              return node.attrs.isBayAttachment && node.attrs.attachBayId == nodes[0].attrs.bayId && node.attrs.bayClass == nodes[0].attrs.class;
            }
          } else {
            return node.attrs.isBayAttachment && node.attrs.attachBayId == nodes[0].attrs.bayId && node.attrs.bayClass == nodes[0].attrs.class;
          }
        });
        sensorNodes.forEach(x=>x.destroy());
      }

      nodes.forEach((element) => {
        element.destroy();
      });

      this._addTrNodes([], "keydown : delete input []");
    } else if (e.keyCode === 27) {
      // ESC
      console.log("ESC Key down");
      this.parent.closePointDlg();
      this.parent.closeLineDlg();
    }

    if (e.keyCode >= 37 && e.keyCode <= 40) {
      this.parent.propObjX = parseInt(xyShape.attrs.x);
      this.parent.propObjY = parseInt(xyShape.attrs.y);
    }

    e.preventDefault();
  }
  _haveIntersection(r1, r2) {
    return !(r2.x > r1.x + r1.width ||
            r2.x + r2.width < r1.x ||
            r2.y > r1.y + r1.height ||
            r2.y + r2.height < r1.y);
  }

  /* Snapping */
  getLineGuideStops(skipShape) {
    // we can snap to stage borders and the center of the stage
    var vertical = [0, this.stage.width() / 2, this.stage.width()];
    var horizontal = [0, this.stage.height() / 2, this.stage.height()];

    // and we snap over edges and center of each object on the canvas
    this.layer.getChildren().forEach((guideItem) => {
      if (
        guideItem === skipShape ||
        guideItem.attrs.name === "selectionRectangle" ||
        guideItem.attrs.name === "backgroundRect" ||
        guideItem.className === "Transformer"
      ) {
        return;
      }
      var box = guideItem.getClientRect();
      // and we can snap to all edges of shapes
      vertical.push([box.x, box.x + box.width, box.x + box.width / 2]);
      horizontal.push([box.y, box.y + box.height, box.y + box.height / 2]);
    });
    return {
      vertical: vertical.flat(),
      horizontal: horizontal.flat(),
    };
  }
  getObjectSnappingEdges(node) {
    if (node.className === "Transformer") {
      node = node.nodes()[0];
    }

    var box = node.getClientRect();
    var absPos = node.absolutePosition();

    return {
      vertical: [
        {
          guide: Math.round(box.x),
          offset: Math.round(absPos.x - box.x),
          snap: "start",
        },
        {
          guide: Math.round(box.x + box.width / 2),
          offset: Math.round(absPos.x - box.x - box.width / 2),
          snap: "center",
        },
        {
          guide: Math.round(box.x + box.width),
          offset: Math.round(absPos.x - box.x - box.width),
          snap: "end",
        },
      ],
      horizontal: [
        {
          guide: Math.round(box.y),
          offset: Math.round(absPos.y - box.y),
          snap: "start",
        },
        {
          guide: Math.round(box.y + box.height / 2),
          offset: Math.round(absPos.y - box.y - box.height / 2),
          snap: "center",
        },
        {
          guide: Math.round(box.y + box.height),
          offset: Math.round(absPos.y - box.y - box.height),
          snap: "end",
        },
      ],
    };
  }
  getGuides(lineGuideStops, itemBounds) {
    var resultV = [];
    var resultH = [];

    lineGuideStops.vertical.forEach((lineGuide) => {
      itemBounds.vertical.forEach((itemBound) => {
        var diff = Math.abs(lineGuide - itemBound.guide);
        // if the distance between guild line and object snap point is close we can consider this for snapping
        if (diff < this.GUIDELINE_OFFSET) {
          resultV.push({
            lineGuide: lineGuide,
            diff: diff,
            snap: itemBound.snap,
            offset: itemBound.offset,
          });
        }
      });
    });

    lineGuideStops.horizontal.forEach((lineGuide) => {
      itemBounds.horizontal.forEach((itemBound) => {
        var diff = Math.abs(lineGuide - itemBound.guide);
        if (diff < this.GUIDELINE_OFFSET) {
          resultH.push({
            lineGuide: lineGuide,
            diff: diff,
            snap: itemBound.snap,
            offset: itemBound.offset,
          });
        }
      });
    });

    var guides = [];

    // find closest snap
    var minV = resultV.sort((a, b) => a.diff - b.diff)[0];
    var minH = resultH.sort((a, b) => a.diff - b.diff)[0];
    if (minV) {
      guides.push({
        lineGuide: minV.lineGuide,
        offset: minV.offset,
        orientation: "V",
        snap: minV.snap,
      });
    }
    if (minH) {
      guides.push({
        lineGuide: minH.lineGuide,
        offset: minH.offset,
        orientation: "H",
        snap: minH.snap,
      });
    }
    return guides;
  }
  drawGuides(guides) {
    guides.forEach((lg) => {
      if (lg.orientation === "H") {
        var line = new Konva.Line({
          points: [-6000, 0, 6000, 0],
          stroke: "rgb(0, 161, 255)",
          strokeWidth: 1,
          name: "guid-line",
          dash: [4, 6],
        });
        this.layer.add(line);
        line.absolutePosition({
          x: 0,
          y: lg.lineGuide,
        });
      } else if (lg.orientation === "V") {
        var line = new Konva.Line({
          points: [0, -6000, 0, 6000],
          stroke: "rgb(0, 161, 255)",
          strokeWidth: 1,
          name: "guid-line",
          dash: [4, 6],
        });
        this.layer.add(line);
        line.absolutePosition({
          x: lg.lineGuide,
          y: 0,
        });
      }
    });
  }

  getTotalBox(boxes) {
    let minX = Infinity;
    let minY = Infinity;
    let maxX = -Infinity;
    let maxY = -Infinity;

    boxes.forEach((box) => {
      minX = Math.min(minX, box.x);
      minY = Math.min(minY, box.y);
      maxX = Math.max(maxX, box.x + box.width);
      maxY = Math.max(maxY, box.y + box.height);
    });
    return {
      x: minX,
      y: minY,
      width: maxX - minX,
      height: maxY - minY,
    };
  }

}
