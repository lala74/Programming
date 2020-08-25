package com.timbuchalka;

public class Main {

    public static void main(String[] args) {
	    boolean gameOver = true;
        int score = 800;
        int levelCompleted = 5;
        int bonus = 100;
        int finalScore;

        finalScore = calculateScore(gameOver, score, levelCompleted, bonus);
        System.out.println("Your final score is : " + finalScore);

        gameOver = false;
        score = 10000;
        levelCompleted = 8;
        bonus = 200;

        finalScore = calculateScore(gameOver, score, levelCompleted, bonus);
        System.out.println("Your final score is : " + finalScore);


        int position;

        position = calculateHighScorePosition(1500);
        displayHighScorePosition("Duc", position);

        position = calculateHighScorePosition(900);
        displayHighScorePosition("Gift", position);

        position = calculateHighScorePosition(400);
        displayHighScorePosition("Lala", position);

        position = calculateHighScorePosition(50);
        displayHighScorePosition("Mon", position);

    }

    public static void displayHighScorePosition(String playerName, int position) {
        System.out.println(playerName + " managed to get into the position " + position + " on the high score table.");
    }

    public static int calculateHighScorePosition(int playerScore) {
        if (playerScore > 1000) {
            return 1;
        } else if (playerScore > 500) {
            return 2;
        } else if (playerScore > 100) {
            return 3;
        } else {
            return 4;
        }
    }

    public static int calculateScore(boolean gameOver, int score, int levelCompleted, int bonus) {
        if (gameOver) {
            int finalScore = score + (levelCompleted * bonus);
            finalScore += 1000;
            return finalScore;
        }
        return -1;
    }
}
