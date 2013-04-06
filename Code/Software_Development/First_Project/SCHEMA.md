Batya Zamansky<br>
Sarah Duncan<br>
Jason Peng<br>
Daryl Sew<br>


Design:

We will have 2 shelves for accessing data.  One shelve will be called questions and will be a dictionary with keys being names and each name will refer to a dictionary of questions. Each question will refer to a list of ratings.  Our second shelve will be called groups and will be a dictionary with keys being names and each name will refer to a list of the people in their group.  The key of names will be first,last,email.

Functions:

<ul> 
     <li>getRatings(email</li>
     <li>addRating(ratee,rater,ratings)</li>
     <li>seeGroupMembers(email)</li>
</ul>

Page Design: <br>

On the main page a user will type in their email and press the login button.  This will lead them to a second page which has two button options:
<ul>
	<li>see ratings</li>
	<li>rate people</li>
</ul>

If the user clicks "see ratings" a page will pop up with all the questions and the ratings that user has received for each question.  It might have statistics as well.  If the user clicks "rate people" it will go to a page with either three buttons with each group member's name, or it will go to a page with a list of group members and a text box.  The user would type in the name of the person in their group that they wanted to rate and press "rate".  This would then go to a page with the questions and the choices, and when the user presses "submit" the ratings will go into the database.
<br><br>

Questions:
<ul>
	<li>How well did this person communicate with the group?</li>
	<li>How well do you think this person did with his/her part of the project?</li>
	<li>How willing would you be to work with this person again?</li>
	<li>How well did the person work in the group overall?</li>
	<li>How many cookies do you think this person deserves for his/her part of the project?</li>
</ul>

