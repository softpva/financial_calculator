import draw from "./draw.js";

class Calculator {
    e_expression = document.querySelector("[data-expression]");
    e_number = document.querySelector("[data-current]");
    s_expression = '';
    s_number = '0';

    constructor() {
        this.clearAll();
        this.buttonEventListener();
    }

    buildNumber(num) {
        if (this.s_expression.includes('=') && this.s_number[0] !== '0') {
            this.s_number = '0';
            this.s_expression = '';
        }
        if (this.s_number.includes('.') && num === '.') return;
        if (this.s_number[0] === '0' && this.s_number[1] !== '.') this.s_number = '';
        this.s_number += num;
        if (this.s_number[0] === '.') this.s_number = "0.";
        this.show();
    }

    buildExpression(op) {
        if (/=/.test(this.s_expression)) this.s_expression = '';
        if (/^-?(0|[1-9]\d*)(\.\d+)?$/.test(this.s_number)) this.s_expression += (this.s_number + ' ');
        this.s_expression += (op + ' ');
        this.s_number = '0';
        this.show();
    }

    equalPressed() {
        if (/^-?(0|[1-9]\d*)(\.\d+)?$/.test(this.s_number)) this.s_expression += (this.s_number + ' ');
        this.s_number = eval(this.s_expression).toString();
        this.s_number = parseFloat(parseFloat(this.s_number).toPrecision(15)).toString();
        this.s_expression += '= ';
    }

    doCommand(com) {
        if (com === '=') this.equalPressed();
        if (com === 'AC') this.clearAll();
        if (com === 'DEL') this.delete();
        if (com === '+/-') this.changeSignal();
        this.show();
    }

    changeSignal() {
        this.s_number = (parseFloat(this.s_number) * -1).toString();
    }

    clearAll() {
        this.s_expression = '';
        this.s_number = '0';
        return;
    }

    delete() {
        if (this.s_number !== '0') {
            this.s_number = this.s_number.slice(0, -1);
            if (this.s_number === '') this.s_number = '0';
            return;
        }
        if (this.s_expression !== '') this.s_expression = this.s_expression.slice(0, -2);

    }

    show() {
        this.e_expression.innerText = this.s_expression;
        this.e_number.innerText = this.s_number;
    }

    buttonEventListener() {
        document.querySelectorAll("[data-num]").forEach(button => {
            button.addEventListener('click', () => {
                this.buildNumber(button.textContent);
            })
        })
        document.querySelectorAll("[data-op]").forEach(button => {
            button.addEventListener('click', () => {
                this.buildExpression(button.textContent);
            })
        })
        document.querySelectorAll("[data-com]").forEach(button => {
            button.addEventListener('click', () => {
                this.doCommand(button.textContent);
            })
        })
    }
}

var canvas = document.getElementById("canvas");
var data = [7, 1, 2, 3, 4, 5, 6, 4, 3, 2, 1];
draw(canvas, data);
// dcs(canvas, data);

const calc = new Calculator();


// function drawCoordinateSystem_pva(canvas, data) {
//     // Get the 2D context for the canvas
//     var ctx = canvas.getContext("2d");
//     // Set the origin at the bottom-left corner of the canvas
//     ctx.translate(0, canvas.height);
//     ctx.scale(1, -1);

//     // Set some properties
//     ctx.textBaseline = 'top';
//     ctx.font = "15px Arial";


//     // Draw the x-axis with tick marks and labels
//     ctx.beginPath();
//     ctx.moveTo(0, 0);
//     ctx.lineTo(canvas.width, 0);
//     for (var i = 0; i < data.length; i++) {
//         var x = (i + 0) * canvas.width / (data.length + 0);
//         var height = data[i] * canvas.height / 10;
//         ctx.moveTo(x, 0);
//         ctx.lineTo(x, height);
//         ctx.stroke();
//         ctx.save();
//         ctx.translate(x + 10, height + 20);
//         ctx.scale(-1, 1)
//         ctx.rotate(Math.PI);
//         ctx.fillText(data[i], 0, 0);
//         //   ctx.fillText(data[i], x - 10, height + 20);
//         ctx.restore();
//     }
//     // Draw the y-axis
//     ctx.beginPath();
//     ctx.moveTo(0, 0);
//     ctx.lineTo(0, canvas.height);
//     ctx.stroke();
// }

// function drawCoordinateSystem_1(canvas, data) {
//     // Get the 2D context for the canvas
//     var ctx = canvas.getContext("2d");

//     // Set the origin at the bottom-left corner of the canvas
//     ctx.translate(0, canvas.height);
//     ctx.scale(1, -1);

//     // Set the text baseline to the top of the text
//     ctx.textBaseline = "top";
//     ctx.font = "15px Arial";

//     // Find the minimum and maximum values in the data array
//     var minValue = Math.min.apply(null, data);
//     var maxValue = Math.max.apply(null, data);

//     // Calculate the scaling factor for the data values
//     var scaleFactor = canvas.height / (maxValue - minValue);

//     // Draw the x-axis with tick marks and labels
//     ctx.beginPath();
//     ctx.moveTo(0, 0);
//     ctx.lineTo(canvas.width, 0);
//     for (var i = 0; i < data.length; i++) {
//         var x = i * canvas.width / (data.length - 1);
//         var height = (data[i] - minValue) * scaleFactor;
//         ctx.moveTo(x, 0);
//         ctx.lineTo(x, height);
//         ctx.stroke();
//         ctx.save();
//         ctx.translate(x, height + 20);
//         ctx.scale(-1, 1); // Flip horizontally
//         ctx.rotate(Math.PI / 2); // Rotate clockwise by 90 degrees
//         ctx.fillText(data[i], 0, 0);
//         ctx.restore();
//     }

//     // Draw the y-axis
//     ctx.beginPath();
//     ctx.moveTo(0, 0);
//     ctx.lineTo(0, canvas.height);
//     ctx.stroke();
// }






