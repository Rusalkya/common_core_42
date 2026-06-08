import React, { useRef, useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import bg from '../assets/background/background.png';
import logo from '../assets/logo/page_title/logo_gribouillit.png';

// Tool icons
import brushIcon from '../assets/logo/canva tools/brush.png';
import eraserIcon from '../assets/logo/canva tools/eraser.png';
import lineIcon from '../assets/logo/canva tools/line.png';
import circleIcon from '../assets/logo/canva tools/circle.png';
import squareIcon from '../assets/logo/canva tools/square.png';
import paintIcon from '../assets/logo/canva tools/paint.png';

export default function AvatarDraw() {
  const canvasRef = useRef(null);
  const ctxRef = useRef(null);
  const navigate = useNavigate();
  const [username, setUsername] = useState('');

  const [drawing, setDrawing] = useState(false);
  const [tool, setTool] = useState('brush');
  const [color, setColor] = useState('#000000');
  const [size, setSize] = useState(5);

  const [startPos, setStartPos] = useState(null);

  const COLORS = [
    '#8B5CF6', // violet
    '#F97316', // orange
    '#22C55E', // vert
    '#EC4899', // rose
    '#3B82F6', // bleu
    '#FACC15', // jaune
    '#10B981', // vert clair
    '#000000', // noir
    '#FFFFFF', // blanc
    '#8B4513'  // marron
  ];

  // ===== GET USERNAME =====
  useEffect(() => {
    const storedUsername = localStorage.getItem('signupUsername');
    if (storedUsername) {
      setUsername(storedUsername);
    }
  }, []);

  // ===== INIT CANVAS =====
  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    
    const ctx = canvas.getContext('2d');
    
    // Reset canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    
    // Fill with white background
    ctx.fillStyle = 'white';
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    
    // Set drawing properties
    ctx.lineCap = 'round';
    ctx.lineJoin = 'round';
    ctx.fillStyle = 'white';
    ctx.strokeStyle = color;
    ctx.lineWidth = size;

    ctxRef.current = ctx;
  }, []);

  useEffect(() => {
    ctxRef.current.strokeStyle = color;
    ctxRef.current.lineWidth = size;
  }, [color, size]);

  // ===== POSITION CORRECTE =====
  const getMousePos = (e) => {
    const rect = canvasRef.current.getBoundingClientRect();
    return {
      x: e.clientX - rect.left,
      y: e.clientY - rect.top
    };
  };

  // ===== START DRAW =====
  const startDrawing = (e) => {
    const pos = getMousePos(e);

    if (tool === 'fill') {
      floodFill(pos.x, pos.y);
      return;
    }

    setDrawing(true);
    setStartPos(pos);

    if (tool === 'brush') {
      ctxRef.current.beginPath();
      ctxRef.current.moveTo(pos.x, pos.y);
    }
  };

  // ===== DRAW =====
  const draw = (e) => {
    if (!drawing) return;

    const pos = getMousePos(e);

    if (tool === 'brush') {
      ctxRef.current.lineTo(pos.x, pos.y);
      ctxRef.current.stroke();
    }
  };

  // ===== STOP DRAW =====
  const stopDrawing = (e) => {
    if (!drawing) return;

    const pos = getMousePos(e);
    const ctx = ctxRef.current;

    if (tool === 'line') {
      ctx.beginPath();
      ctx.moveTo(startPos.x, startPos.y);
      ctx.lineTo(pos.x, pos.y);
      ctx.stroke();
    }

    if (tool === 'rect') {
      ctx.strokeRect(
        startPos.x,
        startPos.y,
        pos.x - startPos.x,
        pos.y - startPos.y
      );
    }

    if (tool === 'circle') {
      const radius = Math.sqrt(
        Math.pow(pos.x - startPos.x, 2) +
        Math.pow(pos.y - startPos.y, 2)
      );

      ctx.beginPath();
      ctx.arc(startPos.x, startPos.y, radius, 0, 2 * Math.PI);
      ctx.stroke();
    }

    ctx.closePath();
    setDrawing(false);
  };

  // ===== FILL TOOL =====
  const floodFill = (x, y) => {
    const canvas = canvasRef.current;
    const ctx = ctxRef.current;
    const imgData = ctx.getImageData(0, 0, canvas.width, canvas.height);
    const data = imgData.data;

    const targetColor = getPixel(data, x, y);
    const fillColor = hexToRgba(color);

    if (colorsMatch(targetColor, fillColor)) return;

    const stack = [[x, y]];

    while (stack.length) {
      const [cx, cy] = stack.pop();
      const idx = (cy * canvas.width + cx) * 4;

      if (!colorsMatch(getPixel(data, cx, cy), targetColor)) continue;

      setPixel(data, cx, cy, fillColor);

      stack.push([cx + 1, cy]);
      stack.push([cx - 1, cy]);
      stack.push([cx, cy + 1]);
      stack.push([cx, cy - 1]);
    }

    ctx.putImageData(imgData, 0, 0);
  };

  const getPixel = (data, x, y) => {
    const i = (y * canvasRef.current.width + x) * 4;
    return data.slice(i, i + 4);
  };

  const setPixel = (data, x, y, color) => {
    const i = (y * canvasRef.current.width + x) * 4;
    data[i] = color[0];
    data[i + 1] = color[1];
    data[i + 2] = color[2];
    data[i + 3] = 255;
  };

  const colorsMatch = (a, b) =>
    a[0] === b[0] && a[1] === b[1] && a[2] === b[2];

  const hexToRgba = (hex) => {
    const bigint = parseInt(hex.slice(1), 16);
    return [
      (bigint >> 16) & 255,
      (bigint >> 8) & 255,
      bigint & 255,
      255
    ];
  };

  // ===== SAVE =====
  const saveImage = () => {
    const link = document.createElement('a');
    const filename = username ? `[${username}]gribouillit.jpg` : 'gribouillit.jpg';
    link.download = filename;
    link.href = canvasRef.current.toDataURL('image/jpeg');
    link.click();
  };

  return (
    <div style={{
      minHeight: '100vh',
      backgroundImage: `url(${bg})`,
      backgroundSize: 'cover',
      backgroundAttachment: 'fixed',
      display: 'flex',
      alignItems: 'flex-start',
      justifyContent: 'center',
      padding: '2rem 1rem'
    }}>

      <div style={{
        width: '1000px',
        background: 'white',
        border: '4px solid black',
        padding: '2rem',
        position: 'relative',
        zIndex: 10
      }}>

        <div style={{
          textAlign: 'center',
          marginBottom: '1.5rem',
          paddingBottom: '1rem',
          borderBottom: '2px solid #ddd'
        }}>
          <img src={logo} alt="Gribouillit" style={{ maxWidth: '100%', height: 'auto', maxHeight: '280px', marginBottom: '1rem' }} />
        </div>

        <h2 style={{ textAlign: 'center', marginBottom: '1.5rem', fontSize: '1.5rem', color: '#000', fontFamily: 'Gribouillit2.0, sans-serif', fontWeight: 'bold', position: 'relative', zIndex: 100 }}>
          Choisir un avatar
        </h2>

        <h1 style={{ textAlign: 'center', marginBottom: '2rem' }}>
          Dessine ton avatar
        </h1>

        {/* CANVAS TOP */}
        <div style={{
          display: 'flex',
          justifyContent: 'center',
          marginBottom: '2rem'
        }}>
          <canvas
            ref={canvasRef}
            width={600}
            height={500}
            style={{
              width: '600px',
              height: '500px',
              border: '3px solid black',
              cursor: 'crosshair',
              backgroundColor: 'white'
            }}
            onMouseDown={startDrawing}
            onMouseMove={draw}
            onMouseUp={stopDrawing}
            onMouseLeave={stopDrawing}
          />
        </div>

        {/* COLORS + TOOLS BOTTOM */}
        <div style={{
          display: 'flex',
          gap: '3rem',
          justifyContent: 'center',
          alignItems: 'flex-start'
        }}>

          {/* COLORS LEFT */}
          <div style={{
            display: 'grid',
            gridTemplateColumns: 'repeat(5, 50px)',
            gap: '8px'
          }}>
            {COLORS.map((c, i) => (
              <div
                key={i}
                onClick={() => setColor(c)}
                style={{
                  width: '50px',
                  height: '50px',
                  backgroundColor: c,
                  border: color === c ? '4px solid #00FEE5' : '2px solid black',
                  cursor: 'pointer',
                  borderRadius: '4px'
                }}
              />
            ))}
          </div>

          {/* TOOLS RIGHT */}
          <div style={{
            display: 'flex',
            flexDirection: 'column',
            gap: '1rem',
            alignItems: 'center'
          }}>
            {/* Tool Buttons - HORIZONTAL */}
            <div style={{ display: 'flex', flexDirection: 'row', gap: '0.5rem' }}>
              <button
                onClick={() => setTool('brush')}
                style={{
                  width: '60px',
                  height: '60px',
                  border: tool === 'brush' ? '4px solid #00FEE5' : '2px solid black',
                  borderRadius: '4px',
                  cursor: 'pointer',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  backgroundColor: 'white'
                }}
                title="Brush"
              >
                <img src={brushIcon} alt="Brush" style={{ width: '40px', height: '40px' }} />
              </button>
              <button
                onClick={() => setTool('line')}
                style={{
                  width: '60px',
                  height: '60px',
                  border: tool === 'line' ? '4px solid #00FEE5' : '2px solid black',
                  borderRadius: '4px',
                  cursor: 'pointer',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  backgroundColor: 'white'
                }}
                title="Line"
              >
                <img src={lineIcon} alt="Line" style={{ width: '40px', height: '40px' }} />
              </button>
              <button
                onClick={() => setTool('rect')}
                style={{
                  width: '60px',
                  height: '60px',
                  border: tool === 'rect' ? '4px solid #00FEE5' : '2px solid black',
                  borderRadius: '4px',
                  cursor: 'pointer',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  backgroundColor: 'white'
                }}
                title="Square"
              >
                <img src={squareIcon} alt="Square" style={{ width: '40px', height: '40px' }} />
              </button>
              <button
                onClick={() => setTool('circle')}
                style={{
                  width: '60px',
                  height: '60px',
                  border: tool === 'circle' ? '4px solid #00FEE5' : '2px solid black',
                  borderRadius: '4px',
                  cursor: 'pointer',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  backgroundColor: 'white'
                }}
                title="Circle"
              >
                <img src={circleIcon} alt="Circle" style={{ width: '40px', height: '40px' }} />
              </button>
            </div>

            {/* SIZE SLIDER */}
            <div style={{
              display: 'flex',
              flexDirection: 'column',
              alignItems: 'center',
              gap: '0.5rem'
            }}>
              <label style={{ fontWeight: 'bold', fontSize: '0.9rem' }}>Taille</label>
              <input
                type="range"
                min="1"
                max="30"
                value={size}
                onChange={(e) => setSize(e.target.value)}
                style={{ width: '60px' }}
              />
              <span style={{ fontSize: '0.85rem' }}>{size}px</span>
            </div>

            {/* SAVE BUTTON */}
            <button
              onClick={saveImage}
              style={{
                width: '60px',
                height: '60px',
                border: '2px solid black',
                borderRadius: '4px',
                cursor: 'pointer',
                fontSize: '1.5rem',
                backgroundColor: 'white'
              }}
              title="Download"
            >
              💾
            </button>
          </div>
        </div>

        {/* VALIDATE BUTTON */}
        <button
          onClick={() => {
            const canvas = canvasRef.current;
            const canvasImage = canvas.toDataURL('image/png');
            localStorage.setItem('avatarDrawing', canvasImage);
            localStorage.setItem('isDrawingMode', 'true');
            navigate('/avatar-step');
          }}
          style={{
            marginTop: '1rem',
            width: '100%',
            padding: '0.75rem',
            fontSize: '1rem',
            backgroundColor: 'black',
            color: '#00FEE5',
            border: '2px solid black',
            borderRadius: '4px',
            cursor: 'pointer',
            fontWeight: 'bold'
          }}
        >
          Valider
        </button>
      </div>
    </div>
  );
}