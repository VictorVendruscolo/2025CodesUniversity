const soma = require('./soma.js');

describe( 'Testes para funcao de soma', () => {
    test('Deve somar 2 + 3 e resultar em 5', () => {
        expect(soma(2,3)).toBe(5);
    });
});