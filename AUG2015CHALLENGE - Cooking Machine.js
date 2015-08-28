/** Codechef **\
 * August 2015 Challenge
 * Cooking Machine
 * Author: Yehya Awad
 * Date: August 11, 2015
 * Status: Correct
 * URL: https://www.codechef.com/AUG15/problems/COOKMACH/
 */

/** Cooking machine class */
var cooker = (function () {
	var operationsCount = 0;

	return {
		decr: {
			odd: function (num) {
				operationsCount += 1;
				return (num - 1) / 2;
			},
			even: function (num) {
				operationsCount += 1;
				return num / 2;
			}
		},
		incr: function (num) {
			operationsCount += 1;
			return num * 2;
		},
		reset: function () {
			operationsCount = 0;
		},
		incrOperations: function () {
			operationsCount += 1;
		},
		getResult: function () {
			return operationsCount;
		}
	};
}());

/** Bunch of useful methods/vars */

var LOG2 = Math.log(2);

function isEven(n) {
	return isNumber(n) && (n % 2 == 0);
}

function isOdd(n) {
	return isNumber(n) && (Math.abs(n) % 2 == 1);
}

function isInt(n) {
	return n % 1 === 0;
}

function isNumber(n) {
	return n == parseFloat(n);
}

function isPowerOf2(n) {
	return isInt(getPowerOf2(n));
}

function getPowerOf2(n) {
	return (Math.log(n) / LOG2);
}

/** Function that solves each problem */
var solve = function (startV, endV) {
	cooker.reset();
	var currentV = startV;

	while ((!isPowerOf2(currentV) && currentV !== 1) || currentV > endV) {
		if (isOdd(currentV)) {
			currentV = cooker.decr.odd(currentV);
		} else {
			currentV = cooker.decr.even(currentV);
		}
	}

	var endPower = getPowerOf2(endV);
	var currPower = getPowerOf2(currentV);
	var powerDiff = endPower - currPower;

	for (i = 0; i < powerDiff; i += 1) {
		cooker.incrOperations();
	}

	return cooker.getResult();
};

process.stdin.resume();
process.stdin.setEncoding('utf8');

/** Main */
process.stdin.on('data', function (chunk) {
	var lines = chunk.toString().split('\n');

	lines.forEach(function (line) {
		if (line === '42') {
			process.exit();
		}

		var numbers = line.split(' ').map(function (item) {
			return parseInt(item, 10);
		});

		if (typeof numbers[1] !== "undefined") {
			process.stdout.write(solve(numbers[0], numbers[1]) + '\n');
		}
	});
});
