/** Codechef **\
 * August 2015 Challenge
 * Gravity Guy
 * Author: Yehya Awad
 * Date: August 11, 2015
 * Status: Partially Correct
 * URL: https://www.codechef.com/AUG15/problems/GRAVGUY/
 */

var yaPrint = function (printText) {
	process.stdout.write(printText + "\n");
};

/** Checks if it is possible to reach the end.
 * Impossible zones
 * #...	..##..	.##..	..#..
 * #... ..##..	..#..	.##..
 */
var isReachable = function (line1, line2, flag) {
	//	process.stdout.write(line1 + " isReachable...? \n");
	var lineLength = line1.length;
	// If start closed or end closed.
	if (line1.charAt(0) === "#" && line2.charAt(0) === "#") {
		return false;
	} else if (line1.charAt(lineLength - 1) === "#" && line2.charAt(lineLength - 1) === "#") {
		return false;
	}

	var i = 0;
	for (i = 0; lineLength > i; i += 1) {
		if (i > 0 && line1.charAt(i) === "#") {
			if (line1.charAt(i - 1) === "#" && line2.charAt(i) === "#") {
				return false;
			}
		} else if (i === (lineLength - 1)) {
			if (line1.charAt(i) === "#" && line2.charAt(i) === "#") {
				return false;
			}
		}
	}

	if (typeof flag === "undefined") {
		return isReachable(line2, line1, true);
	}

	return true;
};

//
//#...#
//.###.
//
//#.#.#.
//.#.#.#
//
//#...
//#...
//
//...#..
//...##.
//
//...#.#.
//...#.#.
//
//...###.
//...#.#.
var cooker = (function () {
	var TOP = 0,
		BOTTOM = 1,
		flipCounter = 0,
		topLine = "",
		bottomLine = "",
		vertPos = TOP,
		horizPos = 0,
		maxSteps = 10,
		minflips = 0;

	return {
		// Completed
		solve: function (level) {
			//			yaPrint("Solving \n" + level.line1 + "\n" + level.line2 + "\n");
			minflips = level.line1.length + 1;
			this.start(level.line1, level.line2);
			this.start(level.line2, level.line1);
			this.printResult();
		},
		// Completed
		start: function (line1, line2) {
			this.reset(line1, line2);
			if (topLine.charAt(0) === "#") {
				vertPos = BOTTOM;
			} else {
				vertPos = TOP;
			}
			this.takeStep();
		},
		// Completed
		end: function () {
			if (flipCounter < minflips) {
				minflips = flipCounter;
			}
		},
		// Completed
		takeStep: function () {
//			this.printPos();
			//			yaPrint("Taking step \nAt " + horizPos + " " + vertPos);
			if (horizPos + 1 < maxSteps) {
				if (this.pathIsClear()) {
					//										yaPrint("Path Clear..\n");
					horizPos += 1;
					this.takeStep();
				} else {
					//										yaPrint("Path NOT clear..\n");
					this.findPath();
				}
			} else {
				this.end();
			}
		},
		// Completed
		pathIsClear: function () {
			if (vertPos === TOP) {
				if (topLine.charAt(horizPos + 1) === "#") {
					return false;
				}
			} else {
				if (bottomLine.charAt(horizPos + 1) === "#") {
					return false;
				}
			}
			return true;
		},
		// Completed
		findPath: function () {
			if (this.flipJump()) {
				horizPos += 1;
			} else {
				this.flip();
			}
			flipCounter += 1;
			this.takeStep();
		},
		// Completed
		flipJump: function () {
			if (vertPos === TOP) {
				if (bottomLine.charAt(horizPos + 1) === "#") {
					return false;
				}
			} else {
				if (topLine.charAt(horizPos + 1) === "#") {
					return false;
				}
			}
			this.flip();
			return true;
		},
		// Completed
		flip: function () {
			if (vertPos === TOP) {
				vertPos = BOTTOM;
			} else {
				vertPos = TOP;
			}
		},
		// Completed
		reset: function (line1, line2) {
			flipCounter = 0;
			horizPos = 0;
			topLine = line1;
			bottomLine = line2;
			maxSteps = line1.length;
		},
		// Completed
		printResult: function () {
			yaPrint(minflips);
		},
		printPos: function () {
			var topLane = topLine;
			var bottomLane = bottomLine;

			if (vertPos === TOP) {
				if (horizPos) {
					topLane = topLine.substring(0, horizPos);
					topLane = topLane + "I";
					topLane = topLane + topLine.substring(horizPos + 1);
				} else {
					topLane = "I";
					topLane = topLane + topLine.substring(1, topLine.length);
				}
			} else {
				if (horizPos) {
					bottomLane = bottomLine.substring(0, horizPos);
					bottomLane = bottomLane + "I";
					bottomLane = bottomLane + bottomLine.substring(horizPos + 1);
				} else {
					bottomLane = "I";
					bottomLane = bottomLane + bottomLine.substring(1, topLine.length);
				}
			}

			yaPrint("----- " + horizPos);
			yaPrint(topLane);
			yaPrint(bottomLane);
		}
	};
}());

process.stdin.resume();
process.stdin.setEncoding('utf8');

process.stdin.on('data', function (chunk) {
	var lines = chunk.toString().split('\n');
	var levels = [];
	var isTop = true;
	var cacheTop = "";
	var isfirstLine = true;

	lines.forEach(function (line) {
		if (line === '42') {
			process.exit();
		}
		if (isfirstLine) {
			isfirstLine = false;
		} else {
			if (isTop) {
				isTop = false;
				cacheTop = line;
			} else {
				isTop = true;
				//				process.stdout.write("Pushing \n");
				//				process.stdout.write("line1: " + cacheTop + "\n");
				//				process.stdout.write("line2: " + line + "\n");
				levels.push({
					line1: cacheTop,
					line2: line,
					isReachable: false
				});
			}
		}
	});

	// Determine if the levels are reachable
	var levelsLength = levels.length;
	//	process.stdout.write(levelsLength + " levels\n");
	var i = 0;
	for (i = 0; levelsLength > i; i += 1) {
		var currentLevel = levels[i];
		//		process.stdout.write("CurrentLevel: " + currentLevel.line1 + "\n");
		currentLevel.isReachable = isReachable(currentLevel.line1, currentLevel.line2);
		// If reachable, then solve.
		if (currentLevel.isReachable) {
			process.stdout.write("Yes" + "\n");
//			cooker.solve(currentLevel);
		} else {
			process.stdout.write("No" + "\n");
		}
		//		process.stdout.write("END \n");
	}
});
