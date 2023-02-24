// When pressing the financial buttons s_number is set to respective varaible.

import draw from "./draw.js";

class Calculator {
    e_expression = document.querySelector("[data-expression]");
    e_number = document.querySelector("[data-current]");
    e_pv = document.querySelector("[data-pv]");
    e_fv = document.querySelector("[data-fv]");
    e_n = document.querySelector("[data-n]");
    e_pn = document.querySelector("[data-pn]");
    e_irn = document.querySelector("[data-irn]");
    e_tot = document.querySelector("[data-tot]");
    s_expression = '';
    s_number = '0';
    n_pv = 0.0;
    n_fv = 0.0;
    i_n = 0;
    n_pn = 0.0;
    n_irn = 0.0;
    n_tot = 0.0;


    constructor() {
        this.clearAll();
        this.buttonEventListener();
    }

    buildNumber(num) {
        if (this.s_expression.includes('=') && this.s_number[0] !== '0') {
            this.s_number = '0';
            this.s_expression = '';
        }
        if (this.s_number[0] === 'T') this.s_number = '';
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
    // change to wasm functions
    calc_fin() {
        // case 2 - works
        // check the formula below & insert total
        if (this.n_pv === 0.0 && this.n_fv >= 0.0 && this.i_n >= 0 && this.n_irn >= 0 && this.n_pn >= 0.0) {
            this.n_pv = (this.n_fv - this.n_pn * (1 + this.n_irn) * ((1 - Math.pow((1 + this.n_irn), this.i_n)) / this.n_irn)) / Math.pow((1 + this.n_irn), this.i_n);
            this.e_pv.innerText = "PV: " + this.round(this.n_pv);
            this.s_number = 'The present value is: ' + this.round(this.n_pv, 5);
            this.n_tot = this.n_fv + this.n_pn * this.i_n;
            this.e_tot.innerText = "Total: " + this.round(this.n_tot);
            return;
        }
        // case 1 - works
        // check the formula below & insert total
        if (this.n_fv === 0.0 && this.n_pv > 0.0 && this.i_n >= 0 && this.n_irn >= 0 && this.n_pn >= 0.0) {
            this.n_fv = this.n_pv * Math.pow((1 + this.n_irn), this.i_n) + this.n_pn * ((Math.pow((1 + this.n_irn), this.i_n) - 1) / this.n_irn);
            this.e_fv.innerText = "FV: " + this.round(this.n_fv);
            this.s_number = 'The future value is: ' + this.round(this.n_fv, 5);
            this.n_tot = this.n_pv + this.n_pn * this.i_n;
            this.e_tot.innerText = "Total: " + this.round(this.n_tot);
            return;
        }

        // case 3 - works
        // check the formula below & insert total
        if (this.i_n === 0 && this.n_pv > 0.0 && this.n_fv > 0.0 && this.n_irn >= 0 && this.n_pn >= 0.0) {
            this.i_n = Math.log((this.n_fv * this.n_irn + this.n_pn) / (this.n_pn + this.n_pv * this.n_irn)) / Math.log(1 + this.n_irn);
            this.e_n.innerText = "n: " + this.i_n;
            this.s_number = 'The number of periods is approximately: ' + Math.floor(this.i_n);
            this.n_tot = this.n_pv + this.n_pn * this.i_n;
            this.e_tot.innerText = "Total: " + this.round(this.n_tot);
            return;
        }

        // case 4  
        // FIXME - the formula below is wrong
        if (this.n_irn === 0.0 && this.n_pv > 0.0 && this.n_fv > 0.0 && this.i_n >= 0) {
            let numerator = (this.n_fv - this.n_pv * Math.pow(1 + this.n_irn, this.i_n)) / this.n_pn;
            let denominator = Math.pow(1 + this.n_irn, this.i_n) - 1;
            console.log(numerator, denominator);
            denominator != 0.0 ? this.n_irn = Math.pow(numerator / denominator, 1 / this.i_n) - 1 : this.n_irn = 0;

            // const numerator = (futureValue - presentValue * Math.pow(1 + r, n)) / payment;
            // const denominator = Math.pow(1 + r, n) - 1;
            // const r = Math.pow(numerator / denominator, 1 / n) - 1;

            // this.n_irn = Math.pow((this.n_fv / this.n_pv), (1 / this.i_n)) - 1;
            this.e_irn.innerText = "IR/n: " + this.round(this.n_irn);
            this.s_number = 'The interest rate is: ' + this.round(this.n_irn * 100, 5) + ' % / period.';
            this.n_tot = this.n_pv + this.n_pn * this.i_n;
            this.e_tot.innerText = "Total: " + this.round(this.n_tot);
            return;
        }
        // case 5
        if (this.n_pv > 0.0 && this.n_fv === 0.0 && this.i_n > 0 && this.n_irn >= 0 && this.n_pn === 0.0) {
            this.n_pn = this.n_pv * this.n_irn;
            this.e_pn.innerText = "P/n: " + this.n_pn;
            this.s_number = 'The payment per period is: ' + this.round(this.n_pn, 5);
            return;
        }
        if (this.n_pn === 0.0) {
            this.n_pn = this.n_pv * this.n_irn;
            this.e_pn.innerText = "P/n: " + this.n_pn;
        }
        // case 6
        // this.tot = this.n_pv + this.pn * this.i_n;
        // this.e_tot.innerText = "Total: " + this.tot;

    }


    equalPressed() {
        if (this.s_number === '0' && this.s_expression === '') {
            this.calc_fin();
            // this.show();            
            return;
        }
        if (/^-?(0|[1-9]\d*)(\.\d+)?$/.test(this.s_number)) this.s_expression += (this.s_number + ' ');
        console.log(this.s_expression);
        this.s_number = eval(this.s_expression).toString();
        this.s_number = parseFloat(parseFloat(this.s_number).toPrecision(15)).toString();
        this.s_expression += '= ';
    }

    round(s_num, prec = 15) {
        return parseFloat(parseFloat(s_num).toPrecision(prec)).toString();
    }

    doCommand(com) {
        if (com === '=') this.equalPressed();
        if (com === 'AC') this.clearAll();
        if (com === 'DEL') this.delete();
        if (com === '+/-') this.changeSignal();
        this.show();
    }

    doFinanc(inner) {
        if (inner === 'PV') {
            this.n_pv = parseFloat(this.s_number);
            this.s_number = '0';
            this.e_pv.innerText = "PV: " + this.n_pv;
        }
        if (inner === 'FV') {
            this.n_fv = parseFloat(this.s_number);
            this.s_number = '0';
            this.e_fv.innerText = "FV: " + this.n_fv;
        }
        if (inner === 'n') {
            this.i_n = parseInt(this.s_number);
            this.s_number = '0';
            this.e_n.innerText = "n: " + this.i_n;
        }
        if (inner === 'IR/n') {
            this.n_irn = parseFloat(this.s_number);
            this.s_number = '0';
            this.e_irn.innerText = "IR/n: " + this.n_irn;
        }
        if (inner === 'P/n') {
            this.n_pn = parseFloat(this.s_number);
            this.s_number = '0';
            this.e_pn.innerText = "P/n: " + this.n_pn;
        }
        this.show();
    }



    changeSignal() {
        this.s_number = (parseFloat(this.s_number) * -1).toString();
    }

    clearAll() {
        this.s_expression = '';
        this.s_number = '0';
        this.e_pv.innerText = 'PV:';
        this.e_fv.innerText = 'FV:';
        this.e_n.innerText = 'n:';
        this.e_irn.innerText = 'IR/n:';
        this.e_pn.innerText = 'P/n:';
        this.e_tot.innerText = 'Total:';
        this.n_pv = 0.0;
        this.n_fv = 0.0;
        this.i_n = 0;
        this.n_irn = 0.0;
        this.n_pn = 0.0;
        this.n_tot = 0.0;
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
        document.querySelectorAll("[data-fin]").forEach(button => {
            button.addEventListener('click', () => {
                this.doFinanc(button.textContent);
            })
        })
    }
}

var canvas = document.getElementById("canvas");
var data = [100, 50, 50, 50, 50, 50, 50, 50, 50, 50, 150];
draw(canvas, data);
// dcs(canvas, data);

const calc = new Calculator();