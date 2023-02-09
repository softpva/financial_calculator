class Calculator {
    e_expression = document.querySelector("[data-expression]");
    e_number = document.querySelector("[data-current]");
    e_memory = document.querySelector("[data-mr]");
    s_expression = '';
    s_number = '0';
    s_memory = '0';

    constructor() {
        this.clearAll();
        this.buttonEventListener();
    }

    buildNumber(num) {
        if (this.s_expression.includes('=') && this.s_number[0] !== '0') this.s_number = '0';
        if (this.s_number.includes('.') && num === '.') return;
        if (this.s_number[0] == '0') this.s_number = '';
        this.s_number += num;
        this.show();
    }

    buildExpression(op) {
        if (this.s_expression.includes('=')) this.s_expression = '';
        let c_penult = this.s_expression.at(-2) || '';
        // console.log("Expr: " + this.s_expression);
        // console.log(c_penult + ' ' + this.s_number[0] + ' ' + op);
        if (c_penult === ')' && this.s_number[0] !== '0') this.s_expression += '* ';
        if (this.s_number[0] !== '0') this.s_expression += (this.s_number + ' ');
        c_penult = this.s_expression.at(-2) || '';
        if (!isNaN(c_penult) && this.s_expression !== '' && op == '(') op = '* (';
        if (op == ')' && this.n_parenthesis() === 0) return;
        this.s_expression += (op + ' ');
        this.s_number = '0';
        this.show();
    }

    equalPressed() {
        if (this.s_expression.at(-2) === ')' && this.s_number[0] !== '0') this.s_expression += '* ';
        if (this.s_number[0] !== '0') this.s_expression += (this.s_number + ' ');
        const n_parenthesis = this.n_parenthesis();
        if (n_parenthesis > 0)
            for (let i = 0; i < n_parenthesis; i++) this.s_expression += ') ';
        console.log("After Equal: " + this.s_expression);
        this.s_number = eval(this.s_expression).toString();
        this.s_number = parseFloat(parseFloat(this.s_number).toPrecision(15)).toString();
        this.s_expression += '= ';
    }

    doCommand(com) {
        if (com === '=') this.equalPressed();
        if (com === 'AC') this.clearAll();
        if (com === 'DEL') this.delete();
        if (com === 'MS') this.setMemory();
        if (com === '+/-') this.changeSignal();
        if (com.toString().includes('MR')) this.s_number = this.s_memory; // <----
        // if (com.slice(0,2) === 'MR') console.log('oi'); // <----
        // console.log(com);
        this.show();
    }

    n_parenthesis() {
        return ((this.s_expression.match(/\(/g) || []).length - (this.s_expression.match(/\)/g) || []).length);
    }

    changeSignal() {
        this.s_number = (parseFloat(this.s_number) * -1).toString();
    }

    setMemory() {
        if (this.s_number === '0') {
            this.s_memory = this.s_number;
            this.e_memory.innerHTML = "MR";
            return;
        }
        this.s_memory = this.s_number;
        this.e_memory.innerHTML = `MR<br/><div class="mem">${this.s_memory.slice(0, 10)}</div>`;
        this.s_number = '0';
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
        document.querySelectorAll("[data-mr]").forEach(button => {
            button.addEventListener('click', () => {
                this.doCommand(button.textContent);
            })
        })
    }
}

const calc = new Calculator();

