var gulp = require('gulp'),
	jshint = require('gulp-jshint'),
	zip = require('gulp-zip');
	webserver = require('gulp-webserver');
 
gulp.task('default', function() {
	return gulp.src('app/scripts/main.js')
      .pipe(jshint())
      .pipe(jshint.reporter('default'));
});

gulp.task('develop', function() {
	return gulp.src('./app/')
		.pipe(webserver({
			livereload: true,
			directoryListing: true,
			fallback: './index.html',
			https: true
		})
	);
});

gulp.task('package', function() {
  // Stuff here
 	return gulp.src('app/*')
        .pipe(zip('vidyowebsample.zip'))
        .pipe(gulp.dest('dist'));
});