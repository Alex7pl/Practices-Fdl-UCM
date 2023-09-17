package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.view.GameSerializer;

public class SerializeCommand extends Command{
	
	private static final String NAME = "serialize";

	private static final String DETAILS = "seriali[z]e";

	private static final String SHORTCUT = "z";

	private static final String HELP = "Serializes the board.";

	public SerializeCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}
	
	private GameSerializer printer;

	@Override
	public boolean execute(Game game) throws CommandExecuteException {
		
		this.printer = new GameSerializer(game);
		
		System.out.println(printer.toString());
		
		return false;
	}
	
}
