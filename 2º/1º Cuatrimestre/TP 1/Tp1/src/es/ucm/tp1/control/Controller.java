package es.ucm.tp1.control;

import java.util.Scanner;

import es.ucm.tp1.control.commands.Command;
import es.ucm.tp1.control.exceptions.GameException;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.view.GamePrinter;

public class Controller {

	private static final String PROMPT = "Command > ";

	private static final String DEBUG_MSG = "[DEBUG] Executing: %s%n";
	private Game game;

	private Scanner scanner;

	private GamePrinter printer;

	public Controller(Game game, Scanner scanner) {
		this.game = game;
		this.scanner = scanner;

		this.printer = new GamePrinter(game);

	}

	public void printGame() {
		System.out.println(printer);
	}

	public void printEndMessage() {
		System.out.println(printer.endMessage());
	}

	public void run() {
		boolean refreshDisplay;
		
		if(game.isFinished()) refreshDisplay = false;
		else refreshDisplay = true;

		while (!game.isFinished()) {
			if (refreshDisplay) {
				printGame();
			}
			refreshDisplay = false;

			System.out.println(PROMPT);
			String s = scanner.nextLine();

			String[] parameters = s.toLowerCase().trim().split(" ");
			System.out.format(DEBUG_MSG, s);
			
			try {
				
				Command command = Command.getCommand(parameters);
				refreshDisplay = command.execute(game);
			}
			catch(GameException ex){
				
				System.out.format(ex.getMessage() + " %n %n");
			}
			
		}
		if (refreshDisplay) {
			printGame();
		}
		printEndMessage();

	}
}
