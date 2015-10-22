/** Codechef **\
 * August 2015 Challenge
 * Grav Guy Generator
 * Author: Yehya Awad
 * Date: August 11, 2015
 * Status: Partially correct (speed)
 * URL: https://www.codechef.com/AUG15/problems/COOKMACH/
 */

var yaPrint = function (printText) {
	//	process.stdout.write(printText);
	console.log(printText);
};

var length = 100;
var myLevel = "";

//AUG2015CHALLENGE - GRAVGUY Level Generator
var i = 0;
for (i = 0; i < length; i += 1) {
	var flag = Math.random() * 10;
	if (flag > 8) {
		myLevel = myLevel + "#";
		//		yaPrint("#");
	} else {
		myLevel = myLevel + ".";
		//		yaPrint(".");
	}
}

yaPrint(myLevel);

yaPrint("\n");
for (i = 0; i < length; i += 1) {
	var flag = Math.random() * 10;
	if (flag > 8) {
		myLevel = myLevel + "#";
		//		yaPrint("#");
	} else {
		myLevel = myLevel + ".";
		//		yaPrint(".");
	}
}
