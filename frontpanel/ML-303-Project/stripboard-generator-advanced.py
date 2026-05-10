#!/usr/bin/env python3
"""
ML-303 Advanced Stripboard Layout Generator
==========================================
Interactive stripboard designer with custom layouts and export options
"""

import json
import os
from typing import List, Dict, Optional, Tuple
from datetime import datetime

class InteractiveStripboardDesigner:
    """Interactive stripboard layout designer with save/load capabilities"""
    
    def __init__(self):
        self.current_design = None
        self.designs_dir = "/Users/jordan_after_midnight/Desktop/ML-303-Project/STRIPBOARD-DESIGNS"
        os.makedirs(self.designs_dir, exist_ok=True)
        
    def create_custom_layout(self):
        """Interactive layout creation"""
        print("\nCUSTOM STRIPBOARD LAYOUT CREATOR")
        print("================================\n")
        
        # Get board dimensions
        width = self._get_int("Board width (holes): ", 5, 50)
        height = self._get_int("Board height (rows): ", 4, 26)
        title = input("Layout title: ").strip() or "Custom Layout"
        
        # Initialize empty board
        board = {
            'title': title,
            'width': width,
            'height': height,
            'components': [],
            'cuts': [],
            'wires': [],
            'notes': []
        }
        
        while True:
            print("\nOptions:")
            print("1. Add component")
            print("2. Add track cut")
            print("3. Add wire/jumper")
            print("4. Add note")
            print("5. View current layout")
            print("6. Save layout")
            print("7. Export as ASCII")
            print("8. Exit")
            
            choice = input("\nChoice (1-8): ").strip()
            
            if choice == '1':
                self._add_component(board)
            elif choice == '2':
                self._add_track_cut(board)
            elif choice == '3':
                self._add_wire(board)
            elif choice == '4':
                self._add_note(board)
            elif choice == '5':
                self._display_board(board)
            elif choice == '6':
                self._save_design(board)
            elif choice == '7':
                self._export_ascii(board)
            elif choice == '8':
                break
                
    def _add_component(self, board: Dict):
        """Add a component to the board"""
        print("\nComponent types:")
        print("1. Resistor")
        print("2. Capacitor")
        print("3. IC/Chip")
        print("4. Button/Switch")
        print("5. LED")
        print("6. Diode")
        print("7. Crystal")
        print("8. Header/Connector")
        print("9. Other")
        
        comp_type = input("Type (1-9): ").strip()
        types = {
            '1': 'resistor', '2': 'capacitor', '3': 'ic',
            '4': 'button', '5': 'led', '6': 'diode',
            '7': 'crystal', '8': 'header', '9': 'other'
        }
        
        if comp_type in types:
            comp = {
                'type': types[comp_type],
                'value': input("Value/Name: ").strip(),
                'start': self._get_position("Start position"),
                'end': None
            }
            
            if input("Multi-hole component? (y/n): ").lower() == 'y':
                comp['end'] = self._get_position("End position")
                
            board['components'].append(comp)
            print("Component added!")
            
    def _add_track_cut(self, board: Dict):
        """Add a track cut"""
        pos = self._get_position("Track cut position")
        board['cuts'].append(pos)
        print("Track cut added!")
        
    def _add_wire(self, board: Dict):
        """Add a wire/jumper"""
        wire = {
            'start': self._get_position("Wire start"),
            'end': self._get_position("Wire end"),
            'color': input("Wire color (optional): ").strip() or "red"
        }
        board['wires'].append(wire)
        print("Wire added!")
        
    def _add_note(self, board: Dict):
        """Add a note to the design"""
        note = input("Note text: ").strip()
        if note:
            board['notes'].append(note)
            print("Note added!")
            
    def _get_position(self, prompt: str) -> Tuple[int, int]:
        """Get a board position from user"""
        while True:
            pos = input(f"{prompt} (e.g., A5 or 0,4): ").strip().upper()
            
            # Try letter+number format
            if len(pos) >= 2 and pos[0].isalpha():
                try:
                    row = ord(pos[0]) - ord('A')
                    col = int(pos[1:]) - 1
                    return (row, col)
                except:
                    pass
                    
            # Try comma-separated format
            if ',' in pos:
                try:
                    row, col = map(int, pos.split(','))
                    return (row, col)
                except:
                    pass
                    
            print("Invalid position. Use format like 'A5' or '0,4'")
            
    def _get_int(self, prompt: str, min_val: int, max_val: int) -> int:
        """Get integer input with validation"""
        while True:
            try:
                val = int(input(prompt))
                if min_val <= val <= max_val:
                    return val
                print(f"Please enter a value between {min_val} and {max_val}")
            except ValueError:
                print("Please enter a valid number")
                
    def _display_board(self, board: Dict):
        """Display current board layout"""
        grid = [['.' for _ in range(board['width'])] for _ in range(board['height'])]
        
        # Add cuts
        for row, col in board['cuts']:
            if 0 <= row < board['height'] and 0 <= col < board['width']:
                grid[row][col] = 'X'
                
        # Add components
        for comp in board['components']:
            row, col = comp['start']
            if 0 <= row < board['height'] and 0 <= col < board['width']:
                symbol = comp['type'][0].upper()
                grid[row][col] = symbol
                
                # Multi-hole components
                if comp['end']:
                    r2, c2 = comp['end']
                    for r in range(min(row, r2), max(row, r2) + 1):
                        for c in range(min(col, c2), max(col, c2) + 1):
                            if 0 <= r < board['height'] and 0 <= c < board['width']:
                                grid[r][c] = symbol
                                
        # Add wires
        for wire in board['wires']:
            r1, c1 = wire['start']
            r2, c2 = wire['end']
            
            if r1 == r2:  # Horizontal
                for c in range(min(c1, c2), max(c1, c2) + 1):
                    if 0 <= c < board['width'] and grid[r1][c] == '.':
                        grid[r1][c] = '-'
            elif c1 == c2:  # Vertical
                for r in range(min(r1, r2), max(r1, r2) + 1):
                    if 0 <= r < board['height'] and grid[r][c1] == '.':
                        grid[r][c1] = '|'
                        
        # Display
        print(f"\n{board['title']}")
        print("=" * len(board['title']))
        print()
        
        # Column headers
        print("    ", end="")
        for i in range(board['width']):
            print(f"{i+1:3}", end="")
        print()
        
        # Grid
        for i, row in enumerate(grid):
            print(f" {chr(65+i)} |", end="")
            for cell in row:
                print(f" {cell} ", end="")
            print("|")
            
        # Legend
        print("\nLegend: R=Resistor, C=Capacitor, I=IC, B=Button, X=Cut, -=Wire")
        
        # Notes
        if board['notes']:
            print("\nNotes:")
            for note in board['notes']:
                print(f"- {note}")
                
    def _save_design(self, board: Dict):
        """Save design to JSON file"""
        filename = input("Save as (without .json): ").strip()
        if not filename:
            filename = f"design_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
            
        filepath = os.path.join(self.designs_dir, f"{filename}.json")
        
        with open(filepath, 'w') as f:
            json.dump(board, f, indent=2)
            
        print(f"Design saved to: {filepath}")
        
    def _export_ascii(self, board: Dict):
        """Export board as detailed ASCII file"""
        filename = input("Export as (without .txt): ").strip()
        if not filename:
            filename = f"export_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
            
        filepath = os.path.join(self.designs_dir, f"{filename}.txt")
        
        with open(filepath, 'w') as f:
            # Write header
            f.write(f"{board['title']}\n")
            f.write("=" * len(board['title']) + "\n\n")
            
            # Write board info
            f.write(f"Board size: {board['height']} rows x {board['width']} columns\n")
            f.write(f"Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
            
            # Write component side
            f.write("COMPONENT SIDE VIEW:\n")
            f.write("-" * 20 + "\n")
            self._write_grid_to_file(f, board, component_side=True)
            
            # Write track side
            f.write("\n\nTRACK SIDE VIEW:\n")
            f.write("-" * 20 + "\n")
            self._write_grid_to_file(f, board, component_side=False)
            
            # Write component list
            f.write("\n\nCOMPONENT LIST:\n")
            f.write("-" * 20 + "\n")
            for i, comp in enumerate(board['components']):
                pos = f"{chr(65+comp['start'][0])}{comp['start'][1]+1}"
                if comp['end']:
                    pos += f"-{chr(65+comp['end'][0])}{comp['end'][1]+1}"
                f.write(f"{i+1}. {comp['type'].title()} {comp['value']}: {pos}\n")
                
            # Write cuts
            if board['cuts']:
                f.write("\n\nTRACK CUTS:\n")
                f.write("-" * 20 + "\n")
                for cut in board['cuts']:
                    f.write(f"- {chr(65+cut[0])}{cut[1]+1}\n")
                    
            # Write wires
            if board['wires']:
                f.write("\n\nWIRE CONNECTIONS:\n")
                f.write("-" * 20 + "\n")
                for wire in board['wires']:
                    start = f"{chr(65+wire['start'][0])}{wire['start'][1]+1}"
                    end = f"{chr(65+wire['end'][0])}{wire['end'][1]+1}"
                    f.write(f"- {start} to {end} ({wire['color']})\n")
                    
            # Write notes
            if board['notes']:
                f.write("\n\nNOTES:\n")
                f.write("-" * 20 + "\n")
                for note in board['notes']:
                    f.write(f"- {note}\n")
                    
        print(f"ASCII layout exported to: {filepath}")
        
    def _write_grid_to_file(self, f, board: Dict, component_side: bool = True):
        """Write grid representation to file"""
        # Create grid
        if component_side:
            grid = [['o' for _ in range(board['width'])] for _ in range(board['height'])]
        else:
            grid = [['=' for _ in range(board['width'])] for _ in range(board['height'])]
            
        # Process based on view
        if component_side:
            # Add components and cuts as before
            for row, col in board['cuts']:
                if 0 <= row < board['height'] and 0 <= col < board['width']:
                    grid[row][col] = 'X'
                    
            for comp in board['components']:
                row, col = comp['start']
                if 0 <= row < board['height'] and 0 <= col < board['width']:
                    symbol = comp['type'][0].upper()
                    grid[row][col] = symbol
                    
                    if comp['end']:
                        r2, c2 = comp['end']
                        for r in range(min(row, r2), max(row, r2) + 1):
                            for c in range(min(col, c2), max(col, c2) + 1):
                                if 0 <= r < board['height'] and 0 <= c < board['width']:
                                    grid[r][c] = symbol
        else:
            # Track side - show cuts breaking tracks
            for row, col in board['cuts']:
                if 0 <= row < board['height']:
                    for c in range(board['width']):
                        if c == col:
                            grid[row][c] = 'X'
                        elif c < col:
                            grid[row][c] = '='
                        else:
                            grid[row][c] = ' '
                            
        # Write column numbers
        f.write("     ")
        for i in range(board['width']):
            f.write(f"{i+1:3}")
        f.write("\n")
        
        # Write separator
        f.write("   +" + "---+" * board['width'] + "\n")
        
        # Write rows
        for i, row in enumerate(grid):
            f.write(f" {chr(65+i)} |")
            for cell in row:
                f.write(f" {cell} |")
            f.write("\n")
            f.write("   +" + "---+" * board['width'] + "\n")
            
    def load_design(self):
        """Load a saved design"""
        designs = [f for f in os.listdir(self.designs_dir) if f.endswith('.json')]
        
        if not designs:
            print("No saved designs found.")
            return
            
        print("\nSaved designs:")
        for i, design in enumerate(designs):
            print(f"{i+1}. {design}")
            
        choice = self._get_int("Load design number: ", 1, len(designs))
        
        filepath = os.path.join(self.designs_dir, designs[choice-1])
        with open(filepath, 'r') as f:
            board = json.load(f)
            
        print(f"Loaded: {board['title']}")
        self._display_board(board)
        
        # Allow editing
        if input("\nEdit this design? (y/n): ").lower() == 'y':
            self.current_design = board
            self.create_custom_layout()

def generate_batch_layouts():
    """Generate multiple standard layouts at once"""
    layouts = {
        'ml303-adapter-simple': {
            'title': 'ML-303 Simple 3-Pin Adapter',
            'width': 10,
            'height': 4,
            'components': [
                {'type': 'button', 'value': '12x12mm', 'start': (1, 0), 'end': (2, 1)},
                {'type': 'wire', 'value': 'jumper', 'start': (1, 1), 'end': (1, 5)},
                {'type': 'wire', 'value': 'jumper', 'start': (2, 1), 'end': (2, 6)},
            ],
            'cuts': [(0, 4), (1, 4), (2, 4), (3, 4)],
            'wires': [
                {'start': (1, 1), 'end': (1, 5), 'color': 'blue'},
                {'start': (2, 1), 'end': (2, 6), 'color': 'black'}
            ],
            'notes': [
                'Connects 4-pin tactile switch to ML-303 3-pin footprint',
                'Blue wire: Button signal to Pin 1',
                'Black wire: Button ground to Pin 3'
            ]
        },
        
        'ml303-matrix-mini': {
            'title': 'ML-303 Mini Matrix Scanner (8 buttons)',
            'width': 20,
            'height': 10,
            'components': [
                {'type': 'ic', 'value': 'ATtiny85', 'start': (3, 5), 'end': (6, 5)},
                {'type': 'resistor', 'value': '10K', 'start': (1, 3), 'end': (1, 5)},
                {'type': 'resistor', 'value': '10K', 'start': (1, 7), 'end': (1, 9)},
                {'type': 'capacitor', 'value': '100nF', 'start': (2, 5), 'end': None},
                {'type': 'header', 'value': '10-pin', 'start': (8, 5), 'end': (8, 14)},
            ],
            'cuts': [(3, 10), (4, 10), (5, 10), (6, 10)],
            'wires': [],
            'notes': [
                'Minimal 8-button scanner using ATtiny85',
                'I2C communication to main controller',
                'Suitable for Function buttons only'
            ]
        },
        
        'ml303-test-jig': {
            'title': 'ML-303 Button Test Jig',
            'width': 25,
            'height': 8,
            'components': [
                {'type': 'led', 'value': 'Red', 'start': (2, 5), 'end': None},
                {'type': 'led', 'value': 'Green', 'start': (2, 10), 'end': None},
                {'type': 'resistor', 'value': '220R', 'start': (3, 5), 'end': (3, 7)},
                {'type': 'resistor', 'value': '220R', 'start': (3, 10), 'end': (3, 12)},
                {'type': 'header', 'value': '3-pin test', 'start': (5, 15), 'end': (7, 15)},
            ],
            'cuts': [],
            'wires': [
                {'start': (2, 5), 'end': (5, 15), 'color': 'red'},
                {'start': (2, 10), 'end': (6, 15), 'color': 'green'}
            ],
            'notes': [
                'Test jig for verifying button connections',
                'Red LED: Button pressed indicator',
                'Green LED: Power indicator',
                'Connect to button under test via 3-pin header'
            ]
        }
    }
    
    output_dir = "/Users/jordan_after_midnight/Desktop/ML-303-Project/GENERATED-LAYOUTS"
    os.makedirs(output_dir, exist_ok=True)
    
    for name, layout in layouts.items():
        filepath = os.path.join(output_dir, f"{name}.json")
        with open(filepath, 'w') as f:
            json.dump(layout, f, indent=2)
        print(f"Generated: {name}")
        
    print(f"\nAll layouts saved to: {output_dir}")

def main():
    """Main menu for stripboard designer"""
    designer = InteractiveStripboardDesigner()
    
    while True:
        print("\nML-303 STRIPBOARD DESIGNER")
        print("==========================")
        print("1. Create custom layout")
        print("2. Load saved design")
        print("3. Generate standard layouts")
        print("4. Batch export all designs")
        print("5. Exit")
        
        choice = input("\nChoice (1-5): ").strip()
        
        if choice == '1':
            designer.create_custom_layout()
        elif choice == '2':
            designer.load_design()
        elif choice == '3':
            generate_batch_layouts()
        elif choice == '4':
            # Batch export
            designs = [f for f in os.listdir(designer.designs_dir) if f.endswith('.json')]
            for design_file in designs:
                print(f"Exporting {design_file}...")
                # Load and export each design
        elif choice == '5':
            print("Goodbye!")
            break

if __name__ == "__main__":
    main()